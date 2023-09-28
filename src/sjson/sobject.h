#pragma once

#include "sencodable.h"
#include "sread.h"
#include "swrite.h"

namespace sjson {

//fields:

template<class Value> class member_field : public generic_field<Value> {
public:
    using generic_field<Value>::generic_field;

public:
    const Value &operator=(const Value &value) {
        return generic_field<Value>::operator=(value);
    }

protected:
    void on_encode() override {
    }

    void on_decode() override {
    }
};

template<class Value> using strmap = member_field<std::shared_ptr<std::map<std::string, Value>>>;
template<class Value> using nummap = member_field<std::shared_ptr<std::map<double     , Value>>>;
template<class Item > using vector = member_field<std::shared_ptr<std::vector<Item>           >>;

using boolean = member_field<bool>       ;
using number  = member_field<double>     ;
using string  = member_field<std::string>;

//object:

typedef base_field field;

template<class Class> class object : public generic_object<Class> {
public:
    void decode(const std::string &text, std::string *error) {
        prepare_read_context(text);
        on_decode();
        if (error) {
            *error = last_read_error();
        }
    }

    std::string encode(bool terse = true) {
        prepare_write_context(terse);
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
