#pragma once

#include <any>

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

} //end dash.

#define d_cast(Type) dash::cast<Type>() =
