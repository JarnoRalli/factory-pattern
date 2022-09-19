#pragma once

#include <memory>
#include <string>

#include <factory.hpp>

enum class object_id : int
{
    OBJECT1,
    OBJECT2
};

std::string to_string(object_id const& id)
{
    switch (id) 
    {
    case object_id::OBJECT1:
        return "OBJECT1";
    case object_id::OBJECT2:
        return "OBJECT2";
    default:
        return "UNKNOWN";
    }
}

struct IObject
{
    virtual int get_int() = 0;
    virtual object_id get_object_type() = 0;
};

struct Object1 : public IObject
{
    Object1();
    
    int get_int() final;
    object_id get_object_type() final;

    int my_int;
};

struct Object2 : public IObject
{
    Object2();

    int get_int() final;
    object_id get_object_type() final;

    int my_int;
};

using object_ptr = std::unique_ptr<IObject>;
using createobject_fcn = object_ptr(*)();
using ObjectFactory = Factory<object_ptr, object_id, createobject_fcn>;

int get_registered_creators();