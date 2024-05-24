#include <memory>

#include "factory/object.hpp"
#include "factory/singleton.hpp"
#include "factory/dll_support.hpp"

// Explicit instantiation of the unique_ptr for the IObject.
template class std::unique_ptr<IObject>;

// Explicit instantiation of the factory-object.
template struct Factory<object_ptr, object_type, createobject_fcn>;

// Explicit instantiation of the Singleton-object.
// The singleton instantiated in this library needs to be exported (dllexport) so that
// it can be referenced outside of this library. Each compilation unit has its own
// copy of the static-object. We want the the ObjectFactory, instantiated using
// Singleton<ObjectFactory>::Instance, to be visible to outside as we register 2
// creator functions later on.
template class FACTORY_EXPORT Singleton<Factory<object_ptr, object_type, createobject_fcn> >;

// Register creator functions for both object1 and object2 types.
namespace {
object_ptr object1_creator_fcn()
{
    return std::make_unique<Object1>();
}

object_ptr object2_creator_fcn()
{
    return std::make_unique<Object2>();
}

// Register object1 creator function.
bool b1 = Singleton<ObjectFactory>::Instance().registercreator(object_type::OBJECT1, &object1_creator_fcn);

// Register object2 creator function.
bool b2 = Singleton<ObjectFactory>::Instance().registercreator(object_type::OBJECT2, &object2_creator_fcn);
}  // namespace

Object1::Object1() : my_int(0)
{
}

int Object1::get_int()
{
    return my_int;
};

object_type Object1::get_object_type()
{
    return object_type::OBJECT1;
};

Object2::Object2() : my_int(0)
{
}

int Object2::get_int()
{
    return my_int;
};

object_type Object2::get_object_type()
{
    return object_type::OBJECT2;
};

std::size_t get_nr_registered_creators()
{
    return Singleton<ObjectFactory>::Instance().registered_creators.size();
}