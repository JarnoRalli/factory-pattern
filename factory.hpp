#pragma once

#include <map>
#include <iostream>

template<
    class AbstractProduct,
    typename IdentifierType,
    typename ProductCreator
>
struct Factory
{
    using creator_storage_t = std::map<IdentifierType, ProductCreator>;
    Factory()
    {
        printf("Factory constructor, this: %X\n", this);
    }

    Factory(Factory const& other)
    {
        printf("Factory copy-constructor, this: %X\n", this);
    }

    Factory(Factory const&& other)
    {
        printf("Factory move-constructor, this: %X\n", this);
    }

    ~Factory()
    {
        printf("Factory destructor, this: %X\n", this);
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