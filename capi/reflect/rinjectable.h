#pragma once

#include <map>
#include "rfunction.h"

namespace reflect {

//function table:

class function_table : public dash::extends<function_table, dash::object> {
public:
    void insert(const char *name, const generic_function::ptr &func);
    void erase (const char *name);

    generic_function::ptr find(const char *name);

private:
    std::map<symbol, generic_function::ptr> _functions;
};

void inject_class_function(
    const char *cls_name, const char *fcn_name, const generic_function::ptr &func);

void erase_class_function (const char *cls_name, const char *fcn_name);
void erase_class_functions(const char *cls_name);

//injectable:

template<> struct typeids_of<class injectable> {
    static constexpr const void *value[] = { "injectable", nullptr };
};

class injectable : public dash::extends<injectable, object> {
public:
    generic_function::ptr find_injected_function(const char *name);

    void inject_function(const char *name, const generic_function::ptr &func);
    void erase_function (const char *name);

    void   set_injected_symbol(const symbol &sym);
    symbol injected_symbol    () const;

protected:
    void on_dispose() override;

private:
    function_table::ptr _injected_fcns;
    symbol              _injected_sym ;
};

} //end reflect.
