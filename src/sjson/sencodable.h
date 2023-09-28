#pragma once

#include <map>
#include <string>
#include "dobject.h"

namespace sjson {

//encodable:

class encodable : public dash::virtual_object {
protected:
    virtual void on_encode();
    virtual void on_decode();
};

//base field and object:

class base_field : public encodable {
public:
    base_field(const char *name);
};

class base_object : public encodable {
public:
    base_object();
    ~base_object();

public:
    const std::map<std::string, base_field *> &fields();

protected:
    void collect();
};

//generic field and object:

template<class Value> class generic_field : public base_field {
public:
    using base_field::base_field;

public:
    Value value;

public:
    const Value &operator=(const Value &value) {
        this->value = value;
        return this->value;
    }

    operator const Value &() const {
        return this->value;
    }
};

template<class Class> struct generic_object : base_object {
public:
    typedef std::shared_ptr<Class> ptr;

    struct field : generic_field<ptr> {
        using generic_field<ptr>::generic_field;
    };

public:
    static ptr create() {
        ptr obj = std::make_shared<Class>();
        obj->collect();
        return obj;
    }
};

} //end sjson.
