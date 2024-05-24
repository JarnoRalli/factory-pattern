#pragma once

#include <memory>
#include <string>

#include "factory/factory.hpp"
#include "factory/dll_support.hpp"

/**
 * @enum object_type
 * @brief An enumerator object for identifying different objects
 * @var object_type::OBJECT1
 * Object1
 * @var object_type::OBJECT2
 * Object2
 */
FACTORY_EXPORT enum class object_type : int { OBJECT1, OBJECT2 };

/**
 * @brief Outputs object id in string
 * @param type : type to be converted into a std::string.
 * @return name of the object type.
 */
FACTORY_EXPORT inline std::string to_string(object_type const& type)
{
    switch (type)
    {
        case object_type::OBJECT1:
            return "OBJECT1";
        case object_type::OBJECT2:
            return "OBJECT2";
        default:
            return "UNKNOWN";
    }
}

/**
 * @brief An abstract class (interface)
 */
struct FACTORY_EXPORT IObject
{
    /**
     * @brief Destructor
     */
    virtual ~IObject(){};

    /**
     * @brief Virtual function that returns an integer.
     * @return integer
     */
    virtual int get_int() = 0;

    /**
     * @brief Virtual function that returns object id.
     * @return object id
     */
    virtual object_type get_object_type() = 0;
};

/**
 * @brief An object that implements the IObject interface
 */
struct FACTORY_EXPORT Object1 : public IObject
{
    /**
     * @brief Simple contructor.
     */
    Object1();

    /**
     * @brief Returns value of member variable my_int.
     * @return value of member variable my_int.
     */
    int get_int() final;

    /**
     * @brief Returns object type of this object.
     * @return object id of this object.
     */
    object_type get_object_type() final;

    int my_int;
};

/**
 * @brief An object that implements the IObject interface
 */
struct FACTORY_EXPORT Object2 : public IObject
{
    /**
     * @brief Simple contructor.
     */
    Object2();

    /**
     * @brief Returns value of member variable my_int.
     * @return value of member variable my_int.
     */
    int get_int() final;

    /**
     * @brief Returns object type of this object.
     * @return object id of this object.
     */
    object_type get_object_type() final;

    int my_int;
};

using object_ptr       = std::unique_ptr<IObject>;
using createobject_fcn = object_ptr (*)();
using ObjectFactory    = Factory<object_ptr, object_type, createobject_fcn>;

/**
 * @brief Returns the number of registered creators of the Object-factory singleton instance.
 * @return number of registered creator functions.
 */
FACTORY_EXPORT std::size_t get_nr_registered_creators();
