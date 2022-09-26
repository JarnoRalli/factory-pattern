#pragma once

#include "dll_support.hpp"

/**
 * @brief A class for delivering singleton objects.
 * 
 * The Singleton-class doesn't have constructors, i.e. objects of Singleton-class
 * cannot be created. Intended use is via a static-function called Instance() which
 * returns a reference to a static object of type T.
 * @tparam T type of the object returned by the Instance()-function.
 */
template <class T>
class FACTORY_EXPORT Singleton
{
public:
    Singleton()                  = delete;
    Singleton(const Singleton&)  = delete;
    Singleton(const Singleton&&) = delete;

   /**
    * @brief A static function that returns an object of type T
    * @tparam T type of the oject returned
    * @return reference to a static object of type T
    */
    static T& Instance()
    {
        static T obj;
        return obj;
    }
};
