#pragma once

#include <any>
#include <cstdint>

namespace dash {

template<class Type> struct cast {
    Type operator=(const std::any &value) {
        try {
            return std::any_cast<Type>(value);
        } catch (const std::bad_any_cast &) {
            return Type();
        }
    }
};

template<class Type> struct n_cast {
    Type operator=(const std::any &value) {
        const std::type_info &type = value.type();

        if (type == typeid(short  )) { return (Type)std::any_cast<short  >(value); }
        if (type == typeid(int    )) { return (Type)std::any_cast<int    >(value); }
        if (type == typeid(int64_t)) { return (Type)std::any_cast<int64_t>(value); }
        if (type == typeid(float  )) { return (Type)std::any_cast<float  >(value); }
        if (type == typeid(double )) { return (Type)std::any_cast<double >(value); }

        return Type();
    }
};
template<> struct cast<short  > : n_cast<short  > { using n_cast<short  >::operator=; };
template<> struct cast<int    > : n_cast<int    > { using n_cast<int    >::operator=; };
template<> struct cast<int64_t> : n_cast<int64_t> { using n_cast<int64_t>::operator=; };
template<> struct cast<float  > : n_cast<float  > { using n_cast<float  >::operator=; };
template<> struct cast<double > : n_cast<double > { using n_cast<double >::operator=; };

} //end dash.

#define d_cast(Type) dash::cast<Type>() =
