#pragma once

#include <any>
#include <string>
#include "dbytes.h"

namespace hpc {

class any {
public:
    any();

    any(bool    value);
    any(int     value);
    any(int64_t value);
    any(float   value);
    any(double  value);

    any(const char            *value);
    any(const std::string     &value);
    any(const dash::bytes_ptr &value);

public:
    operator bool    () const;
    operator int     () const;
    operator int64_t () const;
    operator float   () const;
    operator double  () const;

    operator const char            *() const;
    operator const std::string     &() const;
    operator const dash::bytes_ptr &() const;

private:
    std::any _value;
};

} //end hpc.
