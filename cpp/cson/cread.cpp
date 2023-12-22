#include "cread.h"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <sstream>

namespace cson {

static const char *_cur = nullptr;
static const char *_end = nullptr;

static void skip_space() {
    while (_cur < _end && isspace(*_cur)) {
        _cur += 1;
    }
}

static void throw_except(const char *want) {
    std::stringstream stream;

    if (_cur < _end) {
        const char *end = std::min(_cur + 40, _end);
        stream << "'" << want << "' is expected from: " << std::string(_cur, end);
    } else {
        stream << "'" << want << "' is expected but the stream has ended";
    }

    throw stream.str();
}

void prepare_read_context(const char *begin, const char *end) noexcept {
    _cur = begin;
    _end = end;
}

bool try_read_empty(char first, char last) noexcept {
    skip_space();

    if (_cur + 9 < _end && strncmp(_cur, "undefined", 9) == 0) {
        _cur += 9;
        return true;
    }

    if (_cur + 4 < _end && strncmp(_cur, "null", 4) == 0) {
        _cur += 4;
        return true;
    }

    //"{}" or "[]".
    if (*_cur == first) {
        const char *ptr = _cur + 1;
        while (ptr < _end && isspace(*ptr)) {
            ptr += 1;
        }
        if (ptr < _end && *ptr == last) {
            _cur = ptr + 1;
            return true;
        }
    }

    return false;
}

bool try_read_token(const char *token) noexcept {
    skip_space();

    size_t len = strlen(token);
    if (_cur + len <= _end && strncmp(_cur, token, len) == 0) {
        _cur += len;
        return true;
    }
    return false;
}

char look_forward() noexcept {
    skip_space();

    if (_cur < _end) {
        return *_cur;
    }
    return 0;
}

void read_token(const char *token) {
    skip_space();

    size_t len = strlen(token);
    if (_cur + len <= _end && strncmp(_cur, token, len) == 0) {
        _cur += len;
    } else {
        throw_except(token);
    }
}

double read_double_key() {
    read_token("\"");
    double key = read_double_value();
    read_token("\"");
    return key;
}

std::string read_string_key() {
    return read_string_value();
}

bool read_bool_value() {
    skip_space();

    if (_cur + 5 <= _end && strncmp(_cur, "false", 5) == 0) {
        _cur += 5;
        return false;
    }
    if (_cur + 4 <= _end && strncmp(_cur, "true", 4) == 0) {
        _cur += 4;
        return true;
    }

    throw_except("bool");
    return false;
}

double read_double_value() {
    char  *end = (char *)_end;
    double num = strtod(_cur, &end);

    if (_cur < end) {
        _cur = end;
        return num;
    } else {
        throw_except("double");
        return 0;
    }
}

std::string read_string_value() {
    std::string value;
    read_token("\"");

    while (_cur < _end && *_cur != '\"') {
        if (*_cur == '\\' && _cur + 1 < _end) {
            switch (_cur[1]) {
                case '"' : value.push_back('\"'); break;
                case '\\': value.push_back('\\'); break;
                case '/' : value.push_back('/' ); break;
                case 'b' : value.push_back('\b'); break;
                case 'f' : value.push_back('\f'); break;
                case 'n' : value.push_back('\n'); break;
                case 'r' : value.push_back('\r'); break;
                case 't' : value.push_back('\t'); break;

                default  : value.append(_cur, _cur + 2);
            }
            _cur += 2;

        } else {
            value.push_back(*_cur);
            _cur += 1;
        }
    }

    read_token("\"");
    return value;
}

} //end cson.
