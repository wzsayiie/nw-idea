#pragma once

#include <vector>
#include "cencodable.h"

namespace cson {

void prepare_write_context(bool pretty);

void push_indent ();
void pop_indent  ();
void write_indent();
void write_space ();
void write_line  ();

void write_token(const char        *value);
void write_key  (const double      &value);
void write_key  (const std::string &value);
void write_value(const bool        &value);
void write_value(const double      &value);
void write_value(const std::string &value);

std::string last_write_string();

//for bool, double, string.
template<class Value> struct writer {
    static void write(const Value &value) {
        write_value(value);
    }
};

//for object:
template<> struct writer<encodable_object *> {
    static void write(const encodable_object *obj) {
        if (obj == nullptr) {
            //do not use "null", which is helpful for determining the type.
            write_token("{}");
            return;
        }

        write_token("{");
        write_line();

        const std::map<std::string, encodable_field *> &fields = obj->fields();

        push_indent();
        for (auto it = fields.begin(); it != fields.end(); ) {
            write_indent();
            write_key   (it->first);
            write_token (":");
            write_space ();

            it->second->on_encode();

            if (++it != fields.end()) {
                write_token(",");
            }
            write_line();
        }
        pop_indent();

        write_indent();
        write_token("}");
    }
};

template<class Object> struct writer<std::shared_ptr<Object>> {
    static void write(const std::shared_ptr<Object> &obj) {
        writer<encodable_object *>::write(obj.get());
    }
};

//for map.
template<class Key, class Value> struct writer<std::shared_ptr<std::map<Key, Value>>> {
    static void write(const std::shared_ptr<std::map<Key, Value>> &map) {
        if (!map || map->empty()) {
            write_token("{}");
            return;
        }

        write_token("{");
        write_line();

        push_indent();
        for (auto it = map->begin(); it != map->end(); ) {
            write_indent();
            write_key   (it->first);
            write_token (":");
            write_space ();

            writer<Value>::write(it->second);

            if (++it != map->end()) {
                write_token(",");
            }
            write_line();
        }
        pop_indent();

        write_indent();
        write_token("}");
    }
};

//for vector.
template<class Item> struct writer<std::shared_ptr<std::vector<Item>>> {
    static void write(const std::shared_ptr<std::vector<Item>> &vector) {
        if (!vector || vector->empty()) {
            write_token("[]");
            return;
        }

        write_token("[");
        write_line();

        push_indent();
        for (auto it = vector->begin(); it != vector->end(); ) {
            write_indent();
            writer<Item>::write(*it);

            if (++it != vector->end()) {
                write_token(",");
            }
            write_line();
        }
        pop_indent();

        write_indent();
        write_token("]");
    }
};

} //end cson.
