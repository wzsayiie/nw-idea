#include "hany.h"

namespace hpc {

any::any() {}

any::any(bool    value): _value(         value) {}
any::any(int     value): _value((int64_t)value) {}
any::any(int64_t value): _value(         value) {}
any::any(float   value): _value((double )value) {}
any::any(double  value): _value(         value) {}

any::any(const char            *value): _value(std::string(value ? value : "")) {}
any::any(const std::string     &value): _value(value) {}
any::any(const dash::bytes_ptr &value): _value(value) {}

any::operator bool    () const { return        std::any_cast<bool   >(_value); }
any::operator int     () const { return (int  )std::any_cast<int64_t>(_value); }
any::operator int64_t () const { return        std::any_cast<int64_t>(_value); }
any::operator float   () const { return (float)std::any_cast<double >(_value); }
any::operator double  () const { return        std::any_cast<double >(_value); }

any::operator const char *() const {
    auto str = td::any_cast<const std::string &>(_value);
    return str.c_str();
}

any::operator const std::string &() const {
    return std::any_cast<const std::string &>(_value);
}

any::operator const dash::bytes_ptr &() const {
    return std::any_cast<const dash::bytes_ptr &>(_value);
}

} //end hpc.
