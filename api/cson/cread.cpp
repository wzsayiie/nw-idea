#include "cread.h"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <sstream>

namespace cson {

static const char *g_cur = nullptr;
static const char *g_end = nullptr;

static void skip_space() {
    while (g_cur < g_end && isspace(*g_cur)) {
        g_cur += 1;
    }
}

static void throw_except(const char *want) {
    std::stringstream stream;

    if (g_cur < g_end) {
        const char *end = std::min(g_cur + 40, g_end);
        stream << "'" << want << "' is expected from: " << std::string(g_cur, end);
    } else {
        stream << "'" << want << "' is expected but the stream has ended";
    }

    throw stream.str();
}

void prepare_read_context(const char *begin, const char *end) {
    g_cur = begin;
    g_end = end;
}

bool try_read_empty(char first, char last) {
    skip_space();

    if (g_cur + 9 < g_end && strncmp(g_cur, "undefined", 9) == 0) {
        g_cur += 9;
        return true;
    }

    if (g_cur + 4 < g_end && strncmp(g_cur, "null", 4) == 0) {
        g_cur += 4;
        return true;
    }

    //"{}" or "[]".
    if (*g_cur == first) {
        const char *ptr = g_cur + 1;
        while (ptr < g_end && isspace(*ptr)) {
            ptr += 1;
        }
        if (ptr < g_end && *ptr == last) {
            g_cur = ptr + 1;
            return true;
        }
    }

    return false;
}

bool try_read_token(const char *token) {
    skip_space();

    size_t len = strlen(token);
    if (g_cur + len <= g_end && strncmp(g_cur, token, len) == 0) {
        g_cur += len;
        return true;
    }
    return false;
}

char look_forward() {
    skip_space();

    if (g_cur < g_end) {
        return *g_cur;
    }
    return 0;
}

void read_token(const char *token) {
    skip_space();

    size_t len = strlen(token);
    if (g_cur + len <= g_end && strncmp(g_cur, token, len) == 0) {
        g_cur += len;
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

    if (g_cur + 5 <= g_end && strncmp(g_cur, "false", 5) == 0) {
        g_cur += 5;
        return false;
    }
    if (g_cur + 4 <= g_end && strncmp(g_cur, "true", 4) == 0) {
        g_cur += 4;
        return true;
    }

    throw_except("bool");
    return false;
}

double read_double_value() {
    char  *end = (char *)g_end;
    double num = strtod(g_cur, &end);

    if (g_cur < end) {
        g_cur = end;
        return num;
    } else {
        throw_except("double");
        return 0;
    }
}

std::string read_string_value() {
    std::string value;
    read_token("\"");

    while (g_cur < g_end && *g_cur != '\"') {
        if (*g_cur == '\\' && g_cur + 1 < g_end) {
            switch (g_cur[1]) {
                case '"' : value.push_back('\"'); break;
                case '\\': value.push_back('\\'); break;
                case '/' : value.push_back('/' ); break;
                case 'b' : value.push_back('\b'); break;
                case 'f' : value.push_back('\f'); break;
                case 'n' : value.push_back('\n'); break;
                case 'r' : value.push_back('\r'); break;
                case 't' : value.push_back('\t'); break;

                default  : value.append(g_cur, g_cur + 2);
            }
            g_cur += 2;

        } else {
            value.push_back(*g_cur);
            g_cur += 1;
        }
    }

    read_token("\"");
    return value;
}

} //end cson.
