#pragma once

#include "hpcparam.h"

class HPCSession : public dash::extends<HPCSession, HPCParam> {
public:
    void callback(const std::map<std::string, std::any> &args);
    void callback(const std::vector<std::any> &args);
};
