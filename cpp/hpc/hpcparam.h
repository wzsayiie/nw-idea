#pragma once

#include <any>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

class HPCParam {
public:
    HPCParam();
    HPCParam(const HPCParam &that);
    HPCParam(HPCParam &&that);
    ~HPCParam();

public:
    void reset(int64_t sid);
    int64_t sessionID() const;

    void setProcedureName(const char *name);
    std::string procedureName() const;

    void setCallbackID(int64_t callbackID);
    int64_t callbackID() const;

    void setValues(const std::map<std::string, std::any> &values);
    void setValues(const std::vector<std::any> &values);
    void setValue(const char *key, const std::any &value);
    void setValue(int index, const std::any &value);
    std::any value(const char *key) const;
    std::any value(int index) const;

    void setReturned(const std::any &value);
    std::any returned() const;

private:
    int64_t _sessionID = 0;
};
