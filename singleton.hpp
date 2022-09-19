#pragma once

template <class T>
class Singleton
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