#pragma once

#include <map>
#include <iostream>

#include "factory/dll_support.hpp"

/**
 * @brief Factory-class for creating objects of AbstractProduct type.
 *
 * A concrete factory-object can create a family of objects that share a common base class (AbstractProduct).
 * The type of the object being created is defined by the id. Each object has a unique id.
 * Before the factory-object can create any objects, it needs to register creator-functions (ProductCreator) for each
 * id. Each creator-function is identified by an id of type IdentifierType. Creator-functions are stored in a
 * std::map<IdentifierType, ProductCreator>.
 *
 * A concrete factory-type can be defined as follows:
 * @code
 * using object_ptr = std::unique_ptr<IObject>;
 * using createobject_fcn = object_ptr(*)();
 * using ObjectFactory = Factory<object_ptr, std::string, createobject_fcn>;
 * @endcode
 *
 * @tparam AbstractProduct interface (base-class) of the type of objects that the factory creates.
 * @tparam IdentifierType type of the object that identifies between different AbstractProduct types.
 * @tparam ProductCreator type (signature) of the function that creates specific AbstractProducts.
 */
template <class AbstractProduct, typename IdentifierType, typename ProductCreator>
struct FACTORY_EXPORT Factory
{
    using creator_storage_t = std::map<IdentifierType, ProductCreator>;
    Factory()
    {
    }

    Factory(Factory const& other)
    {
    }

    Factory(Factory const&& other)
    {
    }

    ~Factory()
    {
    }

    /**
     * @brief Registers a creator-function to an id.
     * @param id : id of the object that the creator-function creates.
     * @param creator : a function that returns a new object of AbstractProduct type.
     * @return true/false indicating if registering was successful.
     */
    bool registercreator(IdentifierType const& id, ProductCreator creator)
    {
        auto result = registered_creators.try_emplace(id, creator);
        return result.second;
    };

    /**
     * @brief Removes a registered creator-function tied to an id.
     * @param id : id of the creator-function to be removed
     * @return true/false indicating if removal was successful.
     */
    bool unregister(IdentifierType const& id)
    {
        return registered_creators.erase(id) > 0;
    };

    /**
     * @brief Verifies if a creator-function has been registered.
     * @param id : id of the creator-function being verified.
     * @return true/false indicating if a creator-function related to id has been registered.
     */
    bool is_registered(IdentifierType const& id)
    {
        auto itr = registered_creators.find(id);
        if (itr != registered_creators.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief Creates an object that corresponds to id.
     * @param id : id of the object to be created.
     * @return created product or nullptr.
     */
    AbstractProduct createobject(IdentifierType const& id)
    {
        auto itr = registered_creators.find(id);
        if (itr != registered_creators.end())
        {
            return itr->second();
        }
        else
        {
            return nullptr;
        }
    };

    creator_storage_t registered_creators = {};
};
