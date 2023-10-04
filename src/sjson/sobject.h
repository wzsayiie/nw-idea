#pragma once

#include "sencodable.h"
#include "sread.h"
#include "swrite.h"

namespace sjson {

//fields:

template<class Value> class d_exportable store_field : public encodable_field {
public:
    using encodable_field::encodable_field;

public:
    void on_encode() const override {
        writer<Value>::write(this->_value);
    }

    void on_decode() override {
        this->_value = value_reader<Value>::read();
    }

    void on_clear() override {
        this->_value = Value{};
    }

protected:
    Value _value{};
};

//for bool, double field.
template<class Value> class d_exportable field : public store_field<Value> {
public:
    using store_field<Value>::store_field;

public:
    void operator=(const Value &value) {
        this->_value = value;
    }

    operator const Value &() const {
        return this->_value;
    }
};

//for string field.
template<> class d_exportable field<std::string> : public store_field<std::string> {
public:
    using store_field<std::string>::store_field;

public:
    void operator=(const std::string &value) {
        this->_value = value;
    }

    void operator=(const char *value) {
        this->_value = value ? value : "";
    }

    operator const std::string &() const {
        return this->_value;
    }
};

//for object field.
template<class Object> class d_exportable field<std::shared_ptr<Object>>
    : public store_field<std::shared_ptr<Object>>
{
public:
    using store_field<std::shared_ptr<Object>>::store_field;

public:
    void operator=(const std::shared_ptr<Object> &value) {
        this->_value = value;
    }

    operator const std::shared_ptr<Object> &() const {
        return this->_value;
    }

    const std::shared_ptr<Object> &operator->() const {
        return this->_value;
    }

    std::shared_ptr<Object> &operator->() {
        return this->_value;
    }
};

//for map field.
template<class Key, class Value> class d_exportable field<std::map<Key, Value>>
    : public store_field<std::shared_ptr<std::map<Key, Value>>>
{
public:
    using store_field<std::shared_ptr<std::map<Key, Value>>>::store_field;

public:
    void operator=(const std::shared_ptr<std::map<Key, Value>> &value) {
        this->_value = value;
    }

    operator const std::shared_ptr<std::map<Key, Value>> &() const {
        return this->_value;
    }

    const std::shared_ptr<std::map<Key, Value>> &operator->() const {
        return this->_value;
    }

    std::shared_ptr<std::map<Key, Value>> &operator->() {
        return this->_value;
    }

    const Value &operator[](const Key &key) const {
        return (*this->_value)[key];
    }

    Value &operator[](const Key &key) {
        return (*this->_value)[key];
    }
};

//for vector field.
template<class Item> class d_exportable field<std::vector<Item>>
    : public store_field<std::shared_ptr<std::vector<Item>>>
{
public:
    using store_field<std::shared_ptr<std::vector<Item>>>::store_field;

public:
    void operator=(const std::shared_ptr<std::vector<Item>> &value) {
        this->_value = value;
    }

    operator const std::shared_ptr<std::vector<Item>> &() const {
        return this->_value;
    }

    const std::shared_ptr<std::vector<Item>> &operator->() const {
        return this->_value;
    }

    std::shared_ptr<std::vector<Item>> &operator->() {
        return this->_value;
    }

    const Item &operator[](size_t n) const {
        return (*this->_value)[n];
    }

    Item &operator[](size_t n) {
        return (*this->_value)[n];
    }
};

//object:

template<class Class> class d_exportable object : public encodable_object {
public:
    typedef std::shared_ptr<Class> ptr;

public:
    static ptr create() {
        auto obj = std::make_shared<Class>();
        obj->collect();
        return obj;
    }

public:
    void decode(const std::string &text, std::string *error) {
        clear();

        try {
            const char *bgn = text.c_str();
            const char *end = text.c_str() + text.size();
            prepare_read_context(bgn, end);
            value_reader<encodable_object *>::read(this);

        } catch (const std::string &except) {
            if (error) {
                *error = except;
            }
        }
    }

    std::string encode(bool pretty = false) const {
        prepare_write_context(pretty);
        writer<encodable_object *>::write(this);
        return last_write_string();
    }

    void clear() {
        for (const auto &pair : fields()) {
            pair.second->on_clear();
        }
    }
};

} //end sjson.
