#pragma once

#include <vector>
#include "sencodable.h"
#include "sread.h"
#include "swrite.h"

namespace sjson {

//fields:

template<class Value> class member_field : public generic_field<Value> {
public:
    using generic_field<Value>::generic_field;

protected:
    void on_encode() override {
    }

    void on_decode() override {
    }
};

template<class Elem> using vector = member_field<std::shared_ptr<std::vector<Elem>>>;

using boolean = member_field<bool>       ;
using number  = member_field<double>     ;
using string  = member_field<std::string>;

//object:

typedef base_field field;

template<class Class> class object : public generic_object<Class> {
public:
    void decode(const std::string &text, std::string *error) {
        already_read_context(text);
        on_decode();
        if (error) {
            *error = last_read_error();
        }
    }

    std::string encode(bool terse = true) {
        already_write_context(terse);
        on_encode();
        return last_write_string();
    }

protected:
    void on_encode() override {
    }

    void on_decode() override {
    }
};

} //end sjson.
