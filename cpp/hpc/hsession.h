#pragma once

#include "hparam.h"

class HSession : public dash::extends<HSession, HParam> {
public:
    void callback(const std::map<std::string, std::any> &args);
    void callback(const std::vector<std::any> &args);
};
