#pragma once

#include <vector>
#include "sencodable.h"

namespace sjson {

void prepare_read_context(const char *begin, const char *end) noexcept;

bool try_read_empty(char first, char last) noexcept;
bool try_read_token(const char *token) noexcept;
char look_forward() noexcept;

void read_token(const char *token);

double      read_double_key  ();
std::string read_string_key  ();
bool        read_bool_value  ();
double      read_double_value();
std::string read_string_value();

//key reader:
template<class T> struct key_reader;

template<> struct d_exportable key_reader<double> {
    static double read() {
        return read_double_key();
    }
};

template<> struct d_exportable key_reader<std::string> {
    static std::string read() {
        return read_string_key();
    }
};

//value reader:
template<class T> struct value_reader;

template<> struct d_exportable value_reader<bool> {
    static bool read() {
        return read_bool_value();
    }
};

template<> struct d_exportable value_reader<double> {
    static double read() {
        return read_double_value();
    }
};

template<> struct d_exportable value_reader<std::string> {
    static std::string read() {
        return read_string_value();
    }
};

//the specialization for skipping any value.
template<> struct d_exportable value_reader<void> {
    static void read() {
        char fore = look_forward();
        if (fore == '{') {
            //map.
            read_token("{");
            while (true) {
                read_string_key();
                read_token(":");
                value_reader<void>::read();

                if (try_read_token("}")) {
                    break;
                }
                read_token(",");
            }

        } else if (fore == '[') {
            //vector.
            read_token("[");
            while (true) {
                value_reader<void>::read();

                if (try_read_token("]")) {
                    break;
                }
                read_token(",");
            }

        } else if (fore == 'u') {
            //undefined.
            read_token("undefined");

        } else if (fore == 'n') {
            //null.
            read_token("null");

        } else if (fore == 'f') {
            //false.
            read_token("false");

        } else if (fore == 't') {
            //true.
            read_token("true");

        } else if (fore == '\"') {
            //string.
            read_string_value();

        } else {
            //double.
            read_double_value();
        }
    }
};

template<> struct d_exportable value_reader<encodable_object *> {
    static void read(encodable_object *obj) {
        if (try_read_empty('{', '}')) {
            return;
        }

        const std::map<std::string, encodable_field *> &fields = obj->fields();

        read_token("{");
        while (true) {
            std::string key = read_string_key();
            read_token(":");

            auto value = fields.find(key);
            if (value != fields.end()) {
                value->second->on_decode();
            } else {
                value_reader<void>::read();
            }

            if (try_read_token("}")) {
                break;
            }
            read_token(",");
        }
    }
};

template<class Object> struct d_exportable value_reader<std::shared_ptr<Object>> {
    static std::shared_ptr<Object> read() {
        auto obj = Object::create();
        value_reader<encodable_object *>::read(obj.get());
        return obj;
    }
};

template<class Key, class Value>
    struct d_exportable value_reader<std::shared_ptr<std::map<Key, Value>>>
{
    static std::shared_ptr<std::map<Key, Value>> read() {
        //do not distinguish between "null", "undefined" and empty map.
        if (try_read_empty('{', '}')) {
            return std::shared_ptr<std::map<Key, Value>>();
        }

        auto map = std::make_shared<std::map<Key, Value>>();

        read_token("{");
        while (true) {
            auto key = key_reader<Key>::read();
            read_token(":");
            auto value = value_reader<Value>::read();

            map->insert({ key, value });

            if (try_read_token("}")) {
                break;
            }
            read_token(",");
        }

        return map;
    }
};

template<class Item>
    struct d_exportable value_reader<std::shared_ptr<std::vector<Item>>>
{
    static std::shared_ptr<std::vector<Item>> read() {
        if (try_read_empty('[', ']')) {
            return std::shared_ptr<std::vector<Item>>();
        }

        auto vector = std::make_shared<std::vector<Item>>();

        read_token("[");
        while (true) {
            auto item = value_reader<Item>::read();
            vector->push_back(item);

            if (try_read_token("]")) {
                break;
            }
            read_token(",");
        }

        return vector;
    }
};

} //end sjson.
