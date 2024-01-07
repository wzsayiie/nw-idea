#pragma once

#include <any>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace hpc {

class args_session {
public:
    args_session();
    args_session(const args_session &that);
    args_session(args_session &&that);
    ~args_session();

public:
    void reset(int64_t sid);
    int64_t sid() const;

    void set_proc_name(const char *name);
    std::string proc_name() const;

    void set_callback_id(int64_t callback_id);
    int64_t callback_id() const;

    void set_args(const std::map<std::string, std::any> &args);
    void set_args(const std::vector<std::any> &args);
    void set_arg(const char *key, const std::any &value);
    std::any arg(const char *key) const;
    void set_arg(int index, const std::any &value);
    std::any arg(int index) const;

    void set_ret(const std::any &value);
    std::any ret() const;

private:
    int64_t _sid = 0;
};

typedef args_session args;

class session : public args_session {
public:
    using args_session::args_session;

public:
    void callback(const std::map<std::string, std::any> &args) const;
    void callback(const std::vector<std::any> &args) const;
};

} //end hpc.
