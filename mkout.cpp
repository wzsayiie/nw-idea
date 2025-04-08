#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// ......................... "0123456789AB"
const char *const indent   = "            ";
const char *const path_sep = "/";

#if _MSC_VER
    const char *const obj_ext = ".obj";
#else
    const char *const obj_ext = ".o";
#endif

bool exists_at(const string &path) {
    return std::ifstream(path).is_open();
}

string read_path(const string &path) {
    ifstream fs(path);

    stringstream ss;
    ss << fs.rdbuf();

    return ss.str();
}

//return included headers and line numbers.
vector<tuple<string, int>> scan_incs(const string &path) {
    enum class want {
        sign, inc, str
    };

    string      text = read_path(path);
    const char *bgn  = text.c_str();
    const char *end  = text.c_str() + text.size();
    want        next = want::sign;
    int         line = 1;

    vector<tuple<string, int>> incs;
    for (const char *it = bgn; it < end; ) {
        if (*it == ' ' || *it == '\t') {
            it += 1;
            continue;
        }

        //count endlines.
        if (*it == '\r' && it + 1 < end && *(it + 1) == '\n') {
            it += 2;
            line += 1;
            continue;
        }
        if (*it == '\n') {
            it += 1;
            line += 1;
            continue;
        }

        if (next == want::sign && *it == '#') {
            it += 1;
            next = want::inc;
            continue;
        }
        if (next == want::inc && it + 7 < end && !strncmp(it, "include", 7)) {
            it += 7;
            next = want::str;
            continue;
        }
        if (next == want::str && *it == '<') {
            //ignore "#include <xx>", restart.
            it += 1;
            next = want::sign;
            continue;
        }
        if (next == want::str && *it == '"') {
            it += 1;

            const char *head = it;
            while (it < end && *it != '"') {
                it += 1;
            }
            if (it >= end || *it != '"') {
                //no ending character found, terminate.
                break;
            }
            
            if (head + 1 < it) {
                //consider the case of empty string.
                string str{head, it};
                incs.push_back(make_tuple(str, line));
            }
            it += 1;
        }

        //other tokens, restart.
        it += 1;
        next = want::sign;
    }
    
    return incs;
}

string      _cpl_cmd ;
string      _link_cmd;
set<string> _hdr_dirs;
set<string> _src_dirs;
string      _obj_dir ;
string      _out_file;

void parse_args(int argc, const char *argv[]) {
    enum class want {
        none    ,
        cpl_cmd ,
        link_cmd,
        hdr_dirs,
        src_dirs,
        obj_dir ,
        out_file,
    };
    
    want next = want::none;
    for (int i = 1; i < argc; ++i) {
        const char *item = argv[i];
        
        if /**/ (!strcmp(item, "--compile-cmd")) { next = want::cpl_cmd ; }
        else if (!strcmp(item, "--link-cmd"   )) { next = want::link_cmd; }
        else if (!strcmp(item, "--header-dirs")) { next = want::hdr_dirs; }
        else if (!strcmp(item, "--source-dirs")) { next = want::src_dirs; }
        else if (!strcmp(item, "--object-dir" )) { next = want::obj_dir ; }
        else if (!strcmp(item, "--output-file")) { next = want::out_file; }

        else if (next == want::cpl_cmd ) { _cpl_cmd  = item      ; }
        else if (next == want::link_cmd) { _link_cmd = item      ; }
        else if (next == want::hdr_dirs) { _hdr_dirs.insert(item); }
        else if (next == want::src_dirs) { _src_dirs.insert(item); }
        else if (next == want::obj_dir ) { _obj_dir  = item      ; }
        else if (next == want::out_file) { _out_file = item      ; }
    }
    
    if (_cpl_cmd.empty()) {
        cerr << "no compile command" << endl;
        exit(EXIT_FAILURE);
    }
    if (_link_cmd.empty()) {
        cerr << "no link command" << endl;
        exit(EXIT_FAILURE);
    }
    if (_hdr_dirs.empty()) {
        cerr << "no header search directories" << endl;
        exit(EXIT_FAILURE);
    }
    if (_src_dirs.empty()) {
        cerr << "no source search directories" << endl;
        exit(EXIT_FAILURE);
    }
    if (_obj_dir.empty()) {
        cerr << "no object directory" << endl;
        exit(EXIT_FAILURE);
    }
    if (_out_file.empty()) {
        cerr << "no output file" << endl;
        exit(EXIT_FAILURE);
    }
}

string find_hdr_path(vector<tuple<string, int>> *stack, const string &file) {
    for (const string &dir : _hdr_dirs) {
        string path = dir + path_sep + file;
        if (exists_at(path)) {
            return path;
        }
    }
    
    /**/cerr << "not found: " << file << endl;
    if (!stack->empty()) {
        cerr << "from:" << endl;
    }
    for (auto it = stack->rbegin(); it != stack->rend(); ++it) {
        cerr << get<0>(*it) << ":" << get<1>(*it) << endl;
    }
    
    exit(EXIT_FAILURE);
    return "";
}

map<string, string>      _src_deps ;  //[src_path: obj_path].
map<string, set<string>> _path_deps;  //[path: [inc_path_1, inc_path_2, ...]].

void collect_src_paths() {
    for (const string &dir : _src_dirs) {
        filesystem::directory_iterator iterator(dir);
        for (auto &entry : iterator) {
            string name = entry.path().filename().string();

            auto str = name.c_str();
            auto len = name.size ();
            if (len <= 4 || strcmp(str + len - 4, ".cpp")) {
                continue;
            }

            string src = dir      + path_sep + name;
            string obj = _obj_dir + path_sep + name + obj_ext;
            _src_deps[src] = obj;
        }
    }

    if (_src_deps.empty()) {
        /**/cerr << "no found any sources" << endl;
        /**/cerr << "from:" << endl;
        for (const string &dir : _src_dirs) {
            cerr << dir << endl;
        }

        exit(EXIT_FAILURE);
    }
}

void solve_deps(vector<tuple<string, int>> *stack, const string &path) {
    vector<tuple<string, int>> incs = scan_incs(path);
    
    for (const tuple<string, int> &inc : incs) {
        stack->push_back(make_tuple(path, get<1>(inc)));
        
        string hdr_path = find_hdr_path(stack, get<0>(inc));
        _path_deps[path].insert(hdr_path);
        solve_deps(stack, hdr_path);
        
        stack->pop_back();
    }
}

void print_deps(const string &path, set<string> *pass) {
    const set<string> &deps = _path_deps[path];
    for (const string &item : deps) {
        if (pass->find(item) != pass->end()) {
            continue;
        }
        
        pass->insert(item);
        cout << indent << item << " \\" << endl;
        print_deps(item, pass);
    }
}

//using only simple rules,
//the gcc "make" makefile format is compatible ms-vs "nmake" makefile.
void print_make() {
    /**/cout << _out_file << ":" << " \\" << endl;
    for (const auto &pair : _src_deps) {
        cout << indent << pair.second << " \\" << endl;
    }
    /**/cout << endl;

    /**/cout << "\t" << _link_cmd << _out_file << " \\" << endl;
    for (const auto &pair : _src_deps) {
        cout << indent << pair.second << " \\" << endl;
    }
    /**/cout << endl;
    
    for (const auto &pair : _src_deps) {
        cout << pair.second << ":" << " \\" << endl;
        cout << indent << pair.first << " \\" << endl;
        
        set<string> pass;
        print_deps(pair.first, &pass);
        cout << endl;

        cout << "\t" << _cpl_cmd << pair.second << " \\" << endl;
        cout << indent << pair.first << endl;
        cout << endl;
    }
}

int main(int argc, const char *argv[]) {
    parse_args(argc, argv);

    collect_src_paths();

    vector<tuple<string, int>> stack;
    for (const auto &pair : _src_deps) {
        solve_deps(&stack, pair.first);
    }

    print_make();
}
