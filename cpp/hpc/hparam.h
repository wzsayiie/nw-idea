#pragma once

#include <any>
#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include "dbytes.h"
#include "dobject.h"

class HParam : public dash::extends<HParam, dash::object> {
public:
    ~HParam();

public:
    void setSessionID(int64_t sid);
    int64_t sessionID();

    void setProcedureName(const char *name);
    std::string procedureName();

    void setCallbackID(int64_t callbackID);
    int64_t callbackID();

    void setValues(const std::map<std::string, std::any> &values);
    void setValues(const std::vector<std::any> &values);

    void setValue(const char *key, bool               value);
    void setValue(const char *key, int                value);
    void setValue(const char *key, int64_t            value);
    void setValue(const char *key, float              value);
    void setValue(const char *key, double             value);
    void setValue(const char *key, const char        *value);
    void setValue(const char *key, const dash::bytes &value);

    std::any value(const char *key);

    void setValue(int index, bool               value);
    void setValue(int index, int                value);
    void setValue(int index, int64_t            value);
    void setValue(int index, float              value);
    void setValue(int index, double             value);
    void setValue(int index, const char        *value);
    void setValue(int index, const dash::bytes &value);

    std::any value(int index);

    void returnValue(bool               value);
    void returnValue(int                value);
    void returnValue(int64_t            value);
    void returnValue(float              value);
    void returnValue(double             value);
    void returnValue(const char        *value);
    void returnValue(const dash::bytes &value);

    std::any returned();

private:
    int64_t _sessionID = 0;
};
