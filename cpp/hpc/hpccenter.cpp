#include "hpccenter.h"
#include "ddefine.h"
#include "dlazy.h"
#include "hpclow.h"

static d_define(_callProcedures, dash::lazy<
    std::map<std::string, std::function<void (const HPCSession::ptr &)>>
>);

static d_define(_callbackProcedures, dash::lazy<
    std::map<int64_t, std::function<void (const HPCParam::ptr &)>>
>);

static bool onCall(int64_t sessionID) {
    auto session = HPCSession::create();
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
    auto param = HPCParam::create();
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

    hpc_add_call_procedure(onCall);
    hpc_add_callback_procedure(onCallback);
    initialized = true;
}

static void add(const char *name, const std::function<void (const HPCSession::ptr &)> &callback) {
    initializeIfNeeded();
    _callProcedures->insert({ name, callback });
}

_HPCAdder::_HPCAdder(const char *n, void        (*p)(const HPCSession::ptr &)) { add(n, [=](auto s) { p(s); }); }
_HPCAdder::_HPCAdder(const char *n, bool        (*p)(const HPCSession::ptr &)) { add(n, [=](auto s) { s->returnValue(p(s)); }); }
_HPCAdder::_HPCAdder(const char *n, int         (*p)(const HPCSession::ptr &)) { add(n, [=](auto s) { s->returnValue(p(s)); }); }
_HPCAdder::_HPCAdder(const char *n, int64_t     (*p)(const HPCSession::ptr &)) { add(n, [=](auto s) { s->returnValue(p(s)); }); }
_HPCAdder::_HPCAdder(const char *n, float       (*p)(const HPCSession::ptr &)) { add(n, [=](auto s) { s->returnValue(p(s)); }); }
_HPCAdder::_HPCAdder(const char *n, double      (*p)(const HPCSession::ptr &)) { add(n, [=](auto s) { s->returnValue(p(s)); }); }
_HPCAdder::_HPCAdder(const char *n, std::string (*p)(const HPCSession::ptr &)) { add(n, [=](auto s) { s->returnValue(p(s)); }); }
_HPCAdder::_HPCAdder(const char *n, dash::bytes (*p)(const HPCSession::ptr &)) { add(n, [=](auto s) { s->returnValue(p(s)); }); }

_HPCAdder::_HPCAdder(const char *n, void        (*p)()) { add(n, [=](auto s) { p(); }); }
_HPCAdder::_HPCAdder(const char *n, bool        (*p)()) { add(n, [=](auto s) { s->returnValue(p()); }); }
_HPCAdder::_HPCAdder(const char *n, int         (*p)()) { add(n, [=](auto s) { s->returnValue(p()); }); }
_HPCAdder::_HPCAdder(const char *n, int64_t     (*p)()) { add(n, [=](auto s) { s->returnValue(p()); }); }
_HPCAdder::_HPCAdder(const char *n, double      (*p)()) { add(n, [=](auto s) { s->returnValue(p()); }); }
_HPCAdder::_HPCAdder(const char *n, float       (*p)()) { add(n, [=](auto s) { s->returnValue(p()); }); }
_HPCAdder::_HPCAdder(const char *n, std::string (*p)()) { add(n, [=](auto s) { s->returnValue(p()); }); }
_HPCAdder::_HPCAdder(const char *n, dash::bytes (*p)()) { add(n, [=](auto s) { s->returnValue(p()); }); }

static std::any callProcedure(
    const char                                        *name,
    const HPCParam::ptr                               &param,
    const std::function<void (const HPCParam::ptr &)> &callback)
{
    initializeIfNeeded();

    //set parameters.
    param->setProcedureName(name);
    if (callback) {
        _callbackProcedures->insert({ param->callbackID(), callback });
    }
    //call.
    hpc_call(param->sessionID());
    //return.
    return param->returned();
}

std::any HPCCenter::call(
    const char                                        *name,
    const std::map<std::string, std::any>             &args,
    const std::function<void (const HPCParam::ptr &)> &callback)
{
    auto param = HPCParam::create();
    param->setValues(args);
    return callProcedure(name, param, callback);
}

std::any HPCCenter::call(
    const char                                        *name,
    const std::vector<std::any>                       &args,
    const std::function<void (const HPCParam::ptr &)> &callback)
{
    auto param = HPCParam::create();
    param->setValues(args);
    return callProcedure(name, param, callback);
}

std::any HPCCenter::call(
    const char                                        *name,
    const std::function<void (const HPCParam::ptr &)> &callback)
{
    auto param = HPCParam::create();
    return callProcedure(name, param, callback);
}

std::any HPCCenter::call(const char *name, const std::map<std::string, std::any> &args) {
    auto param = HPCParam::create();
    param->setValues(args);
    return callProcedure(name, param, nullptr);
}

std::any HPCCenter::call(const char *name, const std::vector<std::any> &args) {
    auto param = HPCParam::create();
    param->setValues(args);
    return callProcedure(name, param, nullptr);
}

std::any HPCCenter::call(const char *name) {
    auto param = HPCParam::create();
    return callProcedure(name, param, nullptr);
}
