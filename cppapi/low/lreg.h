#pragma once

#include <cstdint>
#include <string>
#include "dbytes.h"

namespace low {
    
const int param_reg_count = 8;

extern bool        b[param_reg_count];
extern int         i[param_reg_count];
extern int64_t     l[param_reg_count];
extern float       f[param_reg_count];
extern double      d[param_reg_count];
extern std::string s[param_reg_count];
extern dash::bytes v[param_reg_count];

extern bool        br;
extern int         ir;
extern int64_t     lr;
extern float       fr;
extern double      dr;
extern std::string sr;
extern dash::bytes vr;

} //end low.
