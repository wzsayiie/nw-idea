#pragma once

#include <memory>
#include "dexport.h"

namespace dash {

//virtual object.
class d_exportable virtual_object {
public:
    virtual ~virtual_object() = default;
};

//basic object:
template<class Class, class Base> class d_exportable _basic_object_generic
    : public Base
{
};

class d_exportable _basic_object
    : public virtual_object
{
public:
    template<class C, class B> using generic = _basic_object_generic<C, B>;
};

template<
    class Class,
    class Base ,
    template<class, class> class Generic = Base::template generic
>
class d_exportable extends
    : public Generic<Class, Base>
{
public:
    template<class C, class B> using generic = Generic<C, B>;

    typedef Base base;
};

//shared object:
template<class Class, class Base> class d_exportable _shared_object_generic
    : public _basic_object::generic<Class, Base>
{
public:
    typedef std::shared_ptr<Class> ptr;

public:
    template<class... Args> static ptr create(Args... args) {
        auto obj = std::make_shared<Class>(args...);
        obj->_weak = obj;
        return obj;
    }

public:
    ptr me() const {
        return std::static_pointer_cast<Class>(this->_weak.lock());
    }
};

class d_exportable _shared_object
    : public extends<_shared_object, _basic_object, _shared_object_generic>
{
    template<class, class> friend class _shared_object_generic;

private:
    std::weak_ptr<_shared_object> _weak;
};

//object.
class d_exportable object
    : public extends<object, _shared_object>
{
};

//the inheritance tree looks like this:
//
//object
//extends               <object, _shared_object, _object_generic>
//_object_generic       <object, _shared_object>
//_shared_object_generic<object, _shared_object>
//_basic_object_generic <object, _shared_object>
//_shared_object
//extends               <_shared_object, _basic_object, _shared_object_generic>
//_shared_object_generic<_shared_object, _basic_object>
//_basic_object_generic <_shared_object, _basic_object>
//_basic_object

} //end dash.
