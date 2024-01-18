#pragma once

#include <functional>
#include "hsession.h"

struct _HAdder {
    _HAdder(const char *name, void        (*procedure)(const HSession::ptr &session));
    _HAdder(const char *name, bool        (*procedure)(const HSession::ptr &session));
    _HAdder(const char *name, int         (*procedure)(const HSession::ptr &session));
    _HAdder(const char *name, int64_t     (*procedure)(const HSession::ptr &session));
    _HAdder(const char *name, float       (*procedure)(const HSession::ptr &session));
    _HAdder(const char *name, double      (*procedure)(const HSession::ptr &session));
    _HAdder(const char *name, std::string (*procedure)(const HSession::ptr &session));
    _HAdder(const char *name, dash::bytes (*procedure)(const HSession::ptr &session));

    _HAdder(const char *name, void        (*procedure)());
    _HAdder(const char *name, bool        (*procedure)());
    _HAdder(const char *name, int         (*procedure)());
    _HAdder(const char *name, int64_t     (*procedure)());
    _HAdder(const char *name, double      (*procedure)());
    _HAdder(const char *name, float       (*procedure)());
    _HAdder(const char *name, std::string (*procedure)());
    _HAdder(const char *name, dash::bytes (*procedure)());
};

struct HCenter {
    static std::any call(
        const char                                      *name,
        const std::map<std::string, std::any>           &args,
        const std::function<void (const HParam::ptr &)> &callback
    );
    static std::any call(
        const char                                      *name,
        const std::vector<std::any>                     &args,
        const std::function<void (const HParam::ptr &)> &callback
    );
    static std::any call(
        const char                                      *name,
        const std::function<void (const HParam::ptr &)> &callback
    );

    static std::any call(const char *name, const std::map<std::string, std::any> &args);
    static std::any call(const char *name, const std::vector<std::any> &args);
    static std::any call(const char *name);
};

#define HCallableProcedure(procedure) \
/**/    static _HAdder _h_unused_##procedure(#procedure, procedure);
