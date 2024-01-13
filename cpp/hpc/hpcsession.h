#pragma once

#include <any>
#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include "hpcparam.h"

class HPCSession : public HPCParam {
public:
    using HPCParam::HPCParam;

public:
    void callback(const std::map<std::string, std::any> &args) const;
    void callback(const std::vector<std::any> &args) const;
};
