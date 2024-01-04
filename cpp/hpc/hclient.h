#pragma once

namespace hpc {

class registrar {
    registrar(const char *name, void            (*fcn)(const session &sess));
    registrar(const char *name, bool            (*fcn)(const session &sess));
    registrar(const char *name, int64_t         (*fcn)(const session &sess));
    registrar(const char *name, double          (*fcn)(const session &sess));
    registrar(const char *name, std::string     (*fcn)(const session &sess));
    registrar(const char *name, dash::bytes_ptr (*fcn)(const session &sess));

    registrar(const char *name, void            (*fcn)());
    registrar(const char *name, bool            (*fcn)());
    registrar(const char *name, int64_t         (*fcn)());
    registrar(const char *name, double          (*fcn)());
    registrar(const char *name, std::string     (*fcn)());
    registrar(const char *name, dash::bytes_ptr (*fcn)());
};

any call(const std::string &name, const args &values, const std::function<void (const args &)> &proc);
any call(const std::string &name, const args &values);
any call(const std::string &name, const std::function<void (const args &)> &proc);
any call(const std::string &name);

} //end hpc.

#define define_callable_procedure(Proc) \
/**/    static hpc::registrar _h_unused_##Proc(#Proc, Proc);
