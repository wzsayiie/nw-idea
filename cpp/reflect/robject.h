#pragma once

#include "dobject.h"
#include "rsymbol.h"

namespace reflect {

//type ids.
template<> struct typeids_of<class object> {
    static constexpr const void *value[] = { "object", nullptr };
};

//object:
template<class Class, class Base> class _object_generic
    : public dash::object::generic<Class, Base>
{
public:
    virtual symbol class_symbol() const {
        return symbol_of<Class>::value();
    }
};

class object
    : public dash::extends<object, dash::object, _object_generic>
{
public:
    //delete resources manually.
    //avoid circular references for cross-language calls.
    void dispose();

protected:
    virtual void on_dispose();

private:
    bool _disposed = false;
};

//cast.
template<class Type> struct pointer_cast_as {
    static std::shared_ptr<Type> from(const object::ptr &obj) {
        return std::dynamic_pointer_cast<Type>(obj);
    }
};

} //end reflect.
