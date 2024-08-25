#include "cwrite.h"
#include "dlazy.h"

namespace cson {

static dash::lazy<std::string> g_context;

static bool g_pretty = false;
static int  g_indent = 0;

void prepare_writeg_context(bool pretty) {
    g_context->clear();

    g_pretty = pretty;
    g_indent = 0;
}

void push_indent() { g_indent += 1; }
void pop_indent () { g_indent -= 1; }

void write_indent() { if (g_pretty) { g_context->append(g_indent * 4, ' '); } }
void write_space () { if (g_pretty) { g_context->append(" ")              ; } }
void write_line  () { if (g_pretty) { g_context->append("\n")             ; } }

void write_token(const char *value) {
    g_context->append(value);
}

void write_key(const double &value) {
    //if a number is used as the key of an object, to be expressed as a string type.
    g_context->append("\"");
    write_value(value);
    g_context->append("\"");
}

void write_key(const std::string &value) {
    write_value(value);
}

void write_value(const bool &value) {
    g_context->append(value ? "true" : "false");
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

    g_context->append(ptr, end);
}

void write_value(const std::string &value) {
    g_context->append("\"");

    for (char ch : value) {
        switch (ch) {
            case '\"': g_context->append("\\\""); break;
            case '\\': g_context->append("\\\\"); break;
            case '/' : g_context->append("\\/" ); break;
            case '\b': g_context->append("\\b" ); break;
            case '\f': g_context->append("\\f" ); break;
            case '\n': g_context->append("\\n" ); break;
            case '\r': g_context->append("\\r" ); break;
            case '\t': g_context->append("\\t" ); break;

            default  : g_context->push_back(ch);
        }
    }

    g_context->append("\"");
}

std::string last_write_string() {
    std::string ret;
    ret.swap(*g_context);
    return ret;
}

} //end cson.
