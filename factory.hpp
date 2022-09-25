#pragma once

#include <map>
#include <iostream>

#include "dll_support.hpp"

template<
    class AbstractProduct,
    typename IdentifierType,
    typename ProductCreator
>
struct FACTORY_EXPORT Factory
{
    using creator_storage_t = std::map<IdentifierType, ProductCreator>;
    Factory()
    {
        printf("Factory constructor, this: %p\n", this);
    }

    Factory(Factory const& other)
    {
        printf("Factory copy-constructor, this: %p\n", this);
    }

    Factory(Factory const&& other)
    {
        printf("Factory move-constructor, this: %p\n", this);
    }

    ~Factory()
    {
        printf("Factory destructor, this: %p\n", this);
    }

    bool registercreator(IdentifierType const& id, ProductCreator creator)
    {
        std::cout << "Factory registering a product-creator function" << std::endl;
        auto result = registered_creators.try_emplace(id, creator);
        return result.second;
    };

    bool unregister(IdentifierType const& id)
    {
        return registered_creators.erase(id) > 0;
    };

    bool is_registered(IdentifierType const& id)
    {
        auto itr = registered_creators.find(id);
        if(itr != registered_creators.end())
        {   return true; 
        }else{
            return false;
        }
    }

    AbstractProduct createobject(IdentifierType const& id)
    {
        auto itr = registered_creators.find(id);
        if(itr != registered_creators.end())
        {
            return itr->second();
        }else{
            return nullptr;
        }
    };

   creator_storage_t registered_creators = {};
};
