#pragma once

#include "dbytes.h"
#include "hsession.h"

namespace hpc {

struct adder {
    adder(const char *name, void        (*proc)(const session &obj));
    adder(const char *name, bool        (*proc)(const session &obj));
    adder(const char *name, int         (*proc)(const session &obj));
    adder(const char *name, int64_t     (*proc)(const session &obj));
    adder(const char *name, float       (*proc)(const session &obj));
    adder(const char *name, double      (*proc)(const session &obj));
    adder(const char *name, std::string (*proc)(const session &obj));
    adder(const char *name, dash::bytes (*proc)(const session &obj));

    adder(const char *name, void        (*proc)());
    adder(const char *name, bool        (*proc)());
    adder(const char *name, int         (*proc)());
    adder(const char *name, int64_t     (*proc)());
    adder(const char *name, double      (*proc)());
    adder(const char *name, float       (*proc)());
    adder(const char *name, std::string (*proc)());
    adder(const char *name, dash::bytes (*proc)());
};

std::any call(
    const char                                    *name,
    const std::map<std::string, std::any>         &args,
    const std::function<void (const hpc::args &)> &proc
);
std::any call(
    const char                                    *name,
    const std::vector<std::any>                   &args,
    const std::function<void (const hpc::args &)> &proc
);
std::any call(
    const char                                    *name,
    const std::function<void (const hpc::args &)> &proc
);

std::any call(const char *name, const std::map<std::string, std::any> &args);
std::any call(const char *name, const std::vector<std::any> &args);
std::any call(const char *name);

} //end hpc.

#define define_callable_procedure(Proc) \
/**/    static hpc::adder _h_unused_##Proc(#Proc, Proc);
