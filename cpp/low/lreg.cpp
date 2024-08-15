#include "lreg.h"

namespace low {

bool        b[param_reg_count];
int         i[param_reg_count];
int64_t     l[param_reg_count];
float       f[param_reg_count];
double      d[param_reg_count];
std::string s[param_reg_count];
dash::bytes v[param_reg_count];

bool        br;
int         ir;
int64_t     lr;
float       fr;
double      dr;
std::string sr;
dash::bytes vr;

} //end low.
