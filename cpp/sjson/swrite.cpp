#include "swrite.h"

namespace sjson {

static std::string _content;

static bool _pretty = false;
static int  _indent = 0;

void prepare_write_context(bool pretty) {
    _content.clear();

    _pretty = pretty;
    _indent = 0;
}

void push_inden() { _indent += 1; }
void pop_inden () { _indent -= 1; }

void write_inden() { if (_pretty) { _content.append(_indent * 4, ' '); } }
void write_space() { if (_pretty) { _content.append(" ")             ; } }
void write_endln() { if (_pretty) { _content.append("\n")            ; } }

void write_token(const char *value) {
    _content.append(value);
}

void write_key(const double &value) {
    //if a number is used as the key of an object, to be expressed as a string type.
    _content.append("\"");
    write_value(value);
    _content.append("\"");
}

void write_key(const std::string &value) {
    write_value(value);
}

void write_value(const bool &value) {
    _content.append(value ? "true" : "false");
}

void write_value(const double &value) {
    std::string string = std::to_string(value);

    //remove "0" at the end.
    const char *ptr = string.c_str();
    const char *end = string.c_str() + string.size();
    while (ptr + 1 < end && end[-1] == '0') {
        end -= 1;
    }
    if (ptr + 1 < end && end[-1] == '.') {
        end -= 1;
    }

    _content.append(ptr, end);
}

void write_value(const std::string &value) {
    _content.append("\"");

    for (char ch : value) {
        switch (ch) {
            case '\"': _content.append("\\\""); break;
            case '\\': _content.append("\\\\"); break;
            case '/' : _content.append("\\/" ); break;
            case '\b': _content.append("\\b" ); break;
            case '\f': _content.append("\\f" ); break;
            case '\n': _content.append("\\n" ); break;
            case '\r': _content.append("\\r" ); break;
            case '\t': _content.append("\\t" ); break;

            default  : _content.push_back(ch);
        }
    }

    _content.append("\"");
}

std::string last_write_string() {
    std::string ret;
    ret.swap(_content);
    return ret;
}

} //end sjson.
