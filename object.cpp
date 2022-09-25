#include <memory>

#include "object.hpp"
#include "singleton.hpp"
#include "dll_support.hpp"

//Explicit instantiation of the unique_ptr for the IObject
template class std::unique_ptr<IObject>;

//Explicit instantiation of the factory-object
template struct Factory<object_ptr, object_id, createobject_fcn>;

//Explicit instantiation of the Singleton-object, this needs to be exported in VS
template class FACTORY_EXPORT Singleton< Factory<object_ptr, object_id, createobject_fcn> >;

//Register creator functions for both object1 and object2 types
namespace {
    object_ptr object1_creator_fcn()
    {
        return std::make_unique<Object1>();
    }

    object_ptr object2_creator_fcn()
    {
        return std::make_unique<Object2>();
    }

    bool b1 = Singleton<ObjectFactory>::Instance().registercreator(object_id::OBJECT1, &object1_creator_fcn);
    bool b2 = Singleton<ObjectFactory>::Instance().registercreator(object_id::OBJECT2, &object2_creator_fcn);
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

std::size_t get_nr_registered_creators()
{
    return Singleton<ObjectFactory>::Instance().registered_creators.size();
}