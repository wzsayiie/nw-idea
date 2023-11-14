#pragma once

#include <map>
#include <string>
#include "dobject.h"

namespace sjson {

class d_exportable encodable_field : public dash::virtual_object {
public:
    encodable_field(const char *name);

public:
    virtual void on_encode() const = 0;
    virtual void on_decode() = 0;
    virtual void on_clear () = 0;
};

class d_exportable encodable_object : public dash::virtual_object {
public:
    encodable_object();
    ~encodable_object();

public:
    const std::map<std::string, encodable_field *> &fields() const;

protected:
    void collect();
};

} //end sjson.
