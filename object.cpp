#include <memory>

#include "object.hpp"
#include "singleton.hpp"

object_ptr object1_creator()
{
    return std::make_unique<Object1>();
}

object_ptr object2_creator()
{
    return std::make_unique<Object2>();
}

bool b1 = Singleton<ObjectFactory>::Instance().registercreator(object_id::OBJECT1, &object1_creator);
bool b2 = Singleton<ObjectFactory>::Instance().registercreator(object_id::OBJECT2, &object2_creator);

int get_registered_creators()
{
    return Singleton<ObjectFactory>::Instance().registered_creators.size();
}

Object1::Object1() : my_int(0)
{}

int Object1::get_int()
{
    return my_int;
};

object_id Object1::get_object_type()
{
    return object_id::OBJECT1;
};

Object2::Object2() : my_int(0)
{}

int Object2::get_int()
{
    return my_int;
};

object_id Object2::get_object_type()
{
    return object_id::OBJECT2;
};