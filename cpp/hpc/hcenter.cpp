#include "hcenter.h"
#include "ddefine.h"
#include "dlazy.h"
#include "hlow.h"

static d_define(_callProcedures, dash::lazy<
    std::map<std::string, std::function<void (const HSession::ptr &)>>
>);

static d_define(_callbackProcedures, dash::lazy<
    std::map<int64_t, std::function<void (const HParam::ptr &)>>
>);

static bool onCall(int64_t sessionID) {
    auto session = HSession::create();
    session->setSessionID(sessionID);

    auto it = _callProcedures->find(session->procedureName());
    if (it == _callProcedures->end()) {
        return false;
    }

    //call.
    it->second(session);

    return true;
}

static bool onCallback(int64_t sessionID) {
    auto param = HParam::create();
    param->setSessionID(sessionID);

    auto it = _callbackProcedures->find(param->callbackID());
    if (it == _callbackProcedures->end()) {
        return false;
    }

    //call.
    it->second(param);
    //remove the callback procedure.
    _callbackProcedures->erase(it);

    return true;
}

static void initializeIfNeeded() {
    static bool initialized = false;
    if (initialized) {
        return;
    }

    h_add_call_procedure(onCall);
    h_add_callback_procedure(onCallback);
    initialized = true;
}

static void add(const char *name, const std::function<void (const HSession::ptr &)> &callback) {
    initializeIfNeeded();
    _callProcedures->insert({ name, callback });
}

_HAdder::_HAdder(const char *n, void        (*p)(const HSession::ptr &)) { add(n, [=](auto s) { p(s);                         }); }
_HAdder::_HAdder(const char *n, bool        (*p)(const HSession::ptr &)) { add(n, [=](auto s) { s->returnValue(p(s));         }); }
_HAdder::_HAdder(const char *n, int         (*p)(const HSession::ptr &)) { add(n, [=](auto s) { s->returnValue(p(s));         }); }
_HAdder::_HAdder(const char *n, int64_t     (*p)(const HSession::ptr &)) { add(n, [=](auto s) { s->returnValue(p(s));         }); }
_HAdder::_HAdder(const char *n, float       (*p)(const HSession::ptr &)) { add(n, [=](auto s) { s->returnValue(p(s));         }); }
_HAdder::_HAdder(const char *n, double      (*p)(const HSession::ptr &)) { add(n, [=](auto s) { s->returnValue(p(s));         }); }
_HAdder::_HAdder(const char *n, std::string (*p)(const HSession::ptr &)) { add(n, [=](auto s) { s->returnValue(p(s).c_str()); }); }
_HAdder::_HAdder(const char *n, dash::bytes (*p)(const HSession::ptr &)) { add(n, [=](auto s) { s->returnValue(p(s));         }); }

_HAdder::_HAdder(const char *n, void        (*p)()) { add(n, [=](auto s) { p();                         }); }
_HAdder::_HAdder(const char *n, bool        (*p)()) { add(n, [=](auto s) { s->returnValue(p());         }); }
_HAdder::_HAdder(const char *n, int         (*p)()) { add(n, [=](auto s) { s->returnValue(p());         }); }
_HAdder::_HAdder(const char *n, int64_t     (*p)()) { add(n, [=](auto s) { s->returnValue(p());         }); }
_HAdder::_HAdder(const char *n, double      (*p)()) { add(n, [=](auto s) { s->returnValue(p());         }); }
_HAdder::_HAdder(const char *n, float       (*p)()) { add(n, [=](auto s) { s->returnValue(p());         }); }
_HAdder::_HAdder(const char *n, std::string (*p)()) { add(n, [=](auto s) { s->returnValue(p().c_str()); }); }
_HAdder::_HAdder(const char *n, dash::bytes (*p)()) { add(n, [=](auto s) { s->returnValue(p());         }); }

static std::any callProcedure(
    const char                                        *name,
    const HParam::ptr                               &param,
    const std::function<void (const HParam::ptr &)> &callback)
{
    initializeIfNeeded();

    //set parameters.
    param->setProcedureName(name);
    if (callback) {
        _callbackProcedures->insert({ param->callbackID(), callback });
    }
    //call.
    h_call(param->sessionID());
    //return.
    return param->returned();
}

std::any HCenter::call(
    const char                                        *name,
    const std::map<std::string, std::any>             &args,
    const std::function<void (const HParam::ptr &)> &callback)
{
    auto param = HParam::create();
    param->setValues(args);
    return callProcedure(name, param, callback);
}

std::any HCenter::call(
    const char                                        *name,
    const std::vector<std::any>                       &args,
    const std::function<void (const HParam::ptr &)> &callback)
{
    auto param = HParam::create();
    param->setValues(args);
    return callProcedure(name, param, callback);
}

std::any HCenter::call(
    const char                                        *name,
    const std::function<void (const HParam::ptr &)> &callback)
{
    auto param = HParam::create();
    return callProcedure(name, param, callback);
}

std::any HCenter::call(const char *name, const std::map<std::string, std::any> &args) {
    auto param = HParam::create();
    param->setValues(args);
    return callProcedure(name, param, nullptr);
}

std::any HCenter::call(const char *name, const std::vector<std::any> &args) {
    auto param = HParam::create();
    param->setValues(args);
    return callProcedure(name, param, nullptr);
}

std::any HCenter::call(const char *name) {
    auto param = HParam::create();
    return callProcedure(name, param, nullptr);
}
