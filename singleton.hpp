#pragma once

#include "dll_support.hpp"

template <class T>
class FACTORY_EXPORT Singleton
{
public:
    Singleton()                  = delete;
    Singleton(const Singleton&)  = delete;
    Singleton(const Singleton&&) = delete;

    static T& Instance()
    {
        static T obj;
        return obj;
    }
};
