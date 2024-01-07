#include "hcpp.h"
#include "dlazy.h"
#include "hlow.h"

namespace hpc {

static dash::lazy<std::map<std::string, std::function<std::any (const session &)>>> _call_procs;
static dash::lazy<std::map<int64_t, std::function<void (const args &)>>> _callback_procs;

static bool on_call(int64_t sid) {
    session obj;
    obj.reset(sid);

    auto it = _call_procs->find(obj.proc_name());
    if (it == _call_procs->end()) {
        return false;
    }

    std::any ret = it->second(obj);
    obj.set_ret(ret);
    return true;
}

static bool on_callback(int64_t sid) {
    args_session obj;
    obj.reset(sid);

    auto it = _callback_procs->find(obj.callback_id());
    if (it == _callback_procs->end()) {
        return false;
    }

    it->second(obj);
    //remove the callback procedure.
    _callback_procs->erase(it);
    return true;
}

static void initialize_if_needed() {
    static bool initialized = false;
    if (initialized) {
        return;
    }

    hpc_add_call_proc(on_call);
    hpc_add_callback_proc(on_callback);
    initialized = true;
}

static void add(const char *name, const std::function<std::any (const session &)> &proc) {
    initialize_if_needed();
    _call_procs->insert({ name, proc });
}

static void listen_callback(int64_t callback_id, const std::function<void (const args &)> &proc) {
    initialize_if_needed();
    _callback_procs->insert({ callback_id, proc });
}

adder::adder(const char *n, void        (*p)(const session &)) { add(n, [=](const session &s) {p(s);return 0;}); }
adder::adder(const char *n, bool        (*p)(const session &)) { add(n, [=](const session &s) { return p(s); }); }
adder::adder(const char *n, int         (*p)(const session &)) { add(n, [=](const session &s) { return p(s); }); }
adder::adder(const char *n, int64_t     (*p)(const session &)) { add(n, [=](const session &s) { return p(s); }); }
adder::adder(const char *n, float       (*p)(const session &)) { add(n, [=](const session &s) { return p(s); }); }
adder::adder(const char *n, double      (*p)(const session &)) { add(n, [=](const session &s) { return p(s); }); }
adder::adder(const char *n, std::string (*p)(const session &)) { add(n, [=](const session &s) { return p(s); }); }
adder::adder(const char *n, dash::bytes (*p)(const session &)) { add(n, [=](const session &s) { return p(s); }); }

adder::adder(const char *n, void        (*p)()) { add(n, [=](const session &s) {p();return 0;}); }
adder::adder(const char *n, bool        (*p)()) { add(n, [=](const session &s) { return p(); }); }
adder::adder(const char *n, int         (*p)()) { add(n, [=](const session &s) { return p(); }); }
adder::adder(const char *n, int64_t     (*p)()) { add(n, [=](const session &s) { return p(); }); }
adder::adder(const char *n, double      (*p)()) { add(n, [=](const session &s) { return p(); }); }
adder::adder(const char *n, float       (*p)()) { add(n, [=](const session &s) { return p(); }); }
adder::adder(const char *n, std::string (*p)()) { add(n, [=](const session &s) { return p(); }); }
adder::adder(const char *n, dash::bytes (*p)()) { add(n, [=](const session &s) { return p(); }); }

std::any call(
    const char                                    *name,
    const std::map<std::string, std::any>         &args,
    const std::function<void (const hpc::args &)> &proc)
{
    args_session obj;

    obj.set_proc_name(name);
    obj.set_args(args);
    listen_callback(obj.callback_id(), proc);

    hpc_call(obj.sid());
    return obj.ret();
}

std::any call(
    const char                                    *name,
    const std::vector<std::any>                   &args,
    const std::function<void (const hpc::args &)> &proc)
{
    args_session obj;

    obj.set_proc_name(name);
    obj.set_args(args);
    listen_callback(obj.callback_id(), proc);

    hpc_call(obj.sid());
    return obj.ret();
}

std::any call(
    const char                                    *name,
    const std::function<void (const hpc::args &)> &proc)
{
    args_session obj;

    obj.set_proc_name(name);
    listen_callback(obj.callback_id(), proc);

    hpc_call(obj.sid());
    return obj.ret();
}

std::any call(const char *name, const std::map<std::string, std::any> &args) {
    args_session obj;

    obj.set_proc_name(name);
    obj.set_args(args);

    hpc_call(obj.sid());
    return obj.ret();
}

std::any call(const char *name, const std::vector<std::any> &args) {
    args_session obj;

    obj.set_proc_name(name);
    obj.set_args(args);

    hpc_call(obj.sid());
    return obj.ret();
}

std::any call(const char *name) {
    args_session obj;

    obj.set_proc_name(name);

    hpc_call(obj.sid());
    return obj.ret();
}

} //end hpc.
