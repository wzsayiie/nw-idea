#pragma once

#include <vector>
#include "sencodable.h"

namespace sjson {

void prepare_write_context(bool terse);

void indent_push  ();
void indent_pop   ();
void write_indent ();
void write_endline();

void write_value(const bool        &value);
void write_value(const double      &value);
void write_value(const std::string &value);

std::string last_write_string();

//for bool, double and string.
template<class Value> struct writer {
    static void write(const Value &value) {
        write_value(value);
    }
};

//for object.
template<> struct writer<std::shared_ptr<Object>> {
    static void write(const std::shared_ptr<Object> &obj) {
    }
};

} //end sjson.
