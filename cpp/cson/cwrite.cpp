#include "cwrite.h"
#include "dlazy.h"

namespace cson {

static dash::lazy<std::string> _context;

static bool _pretty = false;
static int  _indent = 0;

void prepare_write_context(bool pretty) {
    _context->clear();

    _pretty = pretty;
    _indent = 0;
}

void push_indent() { _indent += 1; }
void pop_indent () { _indent -= 1; }

void write_indent() { if (_pretty) { _context->append(_indent * 4, ' '); } }
void write_space () { if (_pretty) { _context->append(" ")             ; } }
void write_line  () { if (_pretty) { _context->append("\n")            ; } }

void write_token(const char *value) {
    _context->append(value);
}

void write_key(const double &value) {
    //if a number is used as the key of an object, to be expressed as a string type.
    _context->append("\"");
    write_value(value);
    _context->append("\"");
}

void write_key(const std::string &value) {
    write_value(value);
}

void write_value(const bool &value) {
    _context->append(value ? "true" : "false");
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

    _context->append(ptr, end);
}

void write_value(const std::string &value) {
    _context->append("\"");

    for (char ch : value) {
        switch (ch) {
            case '\"': _context->append("\\\""); break;
            case '\\': _context->append("\\\\"); break;
            case '/' : _context->append("\\/" ); break;
            case '\b': _context->append("\\b" ); break;
            case '\f': _context->append("\\f" ); break;
            case '\n': _context->append("\\n" ); break;
            case '\r': _context->append("\\r" ); break;
            case '\t': _context->append("\\t" ); break;

            default  : _context->push_back(ch);
        }
    }

    _context->append("\"");
}

std::string last_write_string() {
    std::string ret;
    ret.swap(*_context);
    return ret;
}

} //end cson.
