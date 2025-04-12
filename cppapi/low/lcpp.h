#pragma once

#define define_low_function(Name)               \
/**/    void Name();                            \
/**/    static low::setter _l_unused_##Name(    \
/**/        #Name, Name                         \
/**/    );

namespace low {

struct setter {
    setter(const char *name, void (*func)());
};

} //end low.
