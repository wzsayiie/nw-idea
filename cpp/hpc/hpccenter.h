#pragma once

#include <functional>
#include "dbytes.h"
#include "hpcsession.h"

struct _HPCAdder {
    _HPCAdder(const char *name, void        (*procedure)(const HPCSession &session));
    _HPCAdder(const char *name, bool        (*procedure)(const HPCSession &session));
    _HPCAdder(const char *name, int         (*procedure)(const HPCSession &session));
    _HPCAdder(const char *name, int64_t     (*procedure)(const HPCSession &session));
    _HPCAdder(const char *name, float       (*procedure)(const HPCSession &session));
    _HPCAdder(const char *name, double      (*procedure)(const HPCSession &session));
    _HPCAdder(const char *name, std::string (*procedure)(const HPCSession &session));
    _HPCAdder(const char *name, dash::bytes (*procedure)(const HPCSession &session));

    _HPCAdder(const char *name, void        (*procedure)());
    _HPCAdder(const char *name, bool        (*procedure)());
    _HPCAdder(const char *name, int         (*procedure)());
    _HPCAdder(const char *name, int64_t     (*procedure)());
    _HPCAdder(const char *name, double      (*procedure)());
    _HPCAdder(const char *name, float       (*procedure)());
    _HPCAdder(const char *name, std::string (*procedure)());
    _HPCAdder(const char *name, dash::bytes (*procedure)());
};

struct HPCCenter {
    static std::any call(
        const char                                   *name,
        const std::map<std::string, std::any>        &args,
        const std::function<void (const HPCParam &)> &callback
    );
    static std::any call(
        const char                                   *name,
        const std::vector<std::any>                  &args,
        const std::function<void (const HPCParam &)> &callback
    );
    static std::any call(
        const char                                   *name,
        const std::function<void (const HPCParam &)> &callback
    );

    static std::any call(const char *name, const std::map<std::string, std::any> &args);
    static std::any call(const char *name, const std::vector<std::any> &args);
    static std::any call(const char *name);
};

#define HPCCallableProcedure(procedure) \
/**/    static _HPCAdder _h_unused_##procedure(#procedure, procedure);
