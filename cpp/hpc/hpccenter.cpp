#include "hpccenter.h"
#include "ddefine.h"
#include "dlazy.h"
#include "hpclow.h"

static d_define(_callProcedures, dash::lazy<
    std::map<std::string, std::function<std::any (const HPCSession &)>>
>);

static d_define(_callbackProcedures, dash::lazy<
    std::map<int64_t, std::function<void (const HPCParam &)>>
>);

static bool onCall(int64_t sessionID) {
    HPCSession session;
    session.reset(sessionID);

    auto it = _callProcedures->find(session.procedureName());
    if (it == _callProcedures->end()) {
        return false;
    }

    std::any returned = it->second(session);
    session.setReturned(returned);
    return true;
}

static bool onCallback(int64_t sessionID) {
    HPCParam param;
    param.reset(sessionID);

    auto it = _callbackProcedures->find(param.callbackID());
    if (it == _callbackProcedures->end()) {
        return false;
    }

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

static void add(const char *name, const std::function<std::any (const HPCSession &)> &callback) {
    initializeIfNeeded();
    _callProcedures->insert({ name, callback });
}

static void listenCallback(int64_t callbackID, const std::function<void (const HPCParam &)> &callback) {
    initializeIfNeeded();
    _callbackProcedures->insert({ callbackID, callback });
}

_HPCAdder::_HPCAdder(const char *n, void        (*p)(const HPCSession &)) { add(n, [=](const HPCSession &s) {p(s);return 0;}); }
_HPCAdder::_HPCAdder(const char *n, bool        (*p)(const HPCSession &)) { add(n, [=](const HPCSession &s) { return p(s); }); }
_HPCAdder::_HPCAdder(const char *n, int         (*p)(const HPCSession &)) { add(n, [=](const HPCSession &s) { return p(s); }); }
_HPCAdder::_HPCAdder(const char *n, int64_t     (*p)(const HPCSession &)) { add(n, [=](const HPCSession &s) { return p(s); }); }
_HPCAdder::_HPCAdder(const char *n, float       (*p)(const HPCSession &)) { add(n, [=](const HPCSession &s) { return p(s); }); }
_HPCAdder::_HPCAdder(const char *n, double      (*p)(const HPCSession &)) { add(n, [=](const HPCSession &s) { return p(s); }); }
_HPCAdder::_HPCAdder(const char *n, std::string (*p)(const HPCSession &)) { add(n, [=](const HPCSession &s) { return p(s); }); }
_HPCAdder::_HPCAdder(const char *n, dash::bytes (*p)(const HPCSession &)) { add(n, [=](const HPCSession &s) { return p(s); }); }

_HPCAdder::_HPCAdder(const char *n, void        (*p)()) { add(n, [=](const HPCSession &s) {p();return 0;}); }
_HPCAdder::_HPCAdder(const char *n, bool        (*p)()) { add(n, [=](const HPCSession &s) { return p(); }); }
_HPCAdder::_HPCAdder(const char *n, int         (*p)()) { add(n, [=](const HPCSession &s) { return p(); }); }
_HPCAdder::_HPCAdder(const char *n, int64_t     (*p)()) { add(n, [=](const HPCSession &s) { return p(); }); }
_HPCAdder::_HPCAdder(const char *n, double      (*p)()) { add(n, [=](const HPCSession &s) { return p(); }); }
_HPCAdder::_HPCAdder(const char *n, float       (*p)()) { add(n, [=](const HPCSession &s) { return p(); }); }
_HPCAdder::_HPCAdder(const char *n, std::string (*p)()) { add(n, [=](const HPCSession &s) { return p(); }); }
_HPCAdder::_HPCAdder(const char *n, dash::bytes (*p)()) { add(n, [=](const HPCSession &s) { return p(); }); }

std::any HPCCenter::call(
    const char                                   *name,
    const std::map<std::string, std::any>        &args,
    const std::function<void (const HPCParam &)> &callback)
{
    HPCParam param;

    param.setProcedureName(name);
    param.setValues(args);
    listenCallback(param.callbackID(), callback);

    hpc_call(param.sessionID());
    return param.returned();
}

std::any HPCCenter::call(
    const char                                   *name,
    const std::vector<std::any>                  &args,
    const std::function<void (const HPCParam &)> &callback)
{
    HPCParam param;

    param.setProcedureName(name);
    param.setValues(args);
    listenCallback(param.callbackID(), callback);

    hpc_call(param.sessionID());
    return param.returned();
}

std::any HPCCenter::call(
    const char                                   *name,
    const std::function<void (const HPCParam &)> &callback)
{
    HPCParam param;

    param.setProcedureName(name);
    listenCallback(param.callbackID(), callback);

    hpc_call(param.sessionID());
    return param.returned();
}

std::any HPCCenter::call(const char *name, const std::map<std::string, std::any> &args) {
    HPCParam param;

    param.setProcedureName(name);
    param.setValues(args);

    hpc_call(param.sessionID());
    return param.returned();
}

std::any HPCCenter::call(const char *name, const std::vector<std::any> &args) {
    HPCParam param;

    param.setProcedureName(name);
    param.setValues(args);

    hpc_call(param.sessionID());
    return param.returned();
}

std::any HPCCenter::call(const char *name) {
    HPCParam param;

    param.setProcedureName(name);

    hpc_call(param.sessionID());
    return param.returned();
}
