#include "swrite.h"

namespace sjson {

static std::string _content;

static bool _terse  = false;
static int  _indent = 0;

void prepare_write_context(bool terse) {
    _content.clear();
    _terse = terse;
    _indent = 0;
}

void indent_push() {
    _indent += 1;
}

void indent_pop() {
    _indent -= 1;
}

void write_indent() {
    if (!_terse && _indent > 0) {
        _content.append(_indent * 4, " ");
    }
}

void write_endline() {
    if (!_terse) {
        _content.append("\n");
    }
}

void write_value(const bool &value) {
    _content.append(value ? "true" : "false");
}

void write_value(const double &value) {
    _content.append(std::to_string(value));
}

void write_value(const std::string &value) {
    _content.push_back('\"');

    for (char ch : value) {
        switch (ch) {
            case '\"': _content.append("\\\"");
            case '\\': _content.append("\\\\");
            case '\/': _content.append("\\\/");
            case '\b': _content.append("\\b" );
            case '\f': _content.append("\\f" );
            case '\n': _content.append("\\n" );
            case '\r': _content.append("\\r" );
            case '\t': _content.append("\\t" );

            default  : _content.push_back(ch);
        }
    }

    _content.push_back('\"');
}

std::string last_write_string() {
    std::string ret;
    ret.swap(_content);
    return ret;
}

} //end sjson.
