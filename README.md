![Linux](https://github.com/JarnoRalli/factory-pattern/actions/workflows/linux_build.yml/badge.svg)   ![Windows](https://github.com/JarnoRalli/factory-pattern/actions/workflows/windows_build.yml/badge.svg)   ![Code style](https://github.com/JarnoRalli/factory-pattern/actions/workflows/code_style.yml/badge.svg)

# A Factory Pattern and a Singleton

This repository implements a simple factory-pattern and a singleton in a library called `factory`.

## Singleton

A singleton can be used for creating a single instance of a concrete factory. 
The singleton doesn't have constructors, so objects of this type cannot be created. Intended use
is calling the static function `Instance()` that returns a reference to a static object of type
`<T>`, e.g. `Singleton<Object>::Instance()`. An explicit instantiation of the Singleton template
must be exported from the library using `__declspec(dllexport)` in Visual C++, otherwise the
the returned static-object is not truly 'singular' as each compilation unit will have its own
static-object.

## Factory

This repository implements a factory-pattern template that can be instantiated to create objects
that share a base-class. Creator-functions, that create the actual objects identified by a type id,
are registered in a `std::map` inside a concrete factory-object. Functionality of the factory-pattern 
is showcased using an interface called `IObject`, and two object-classes called `Object1` and `Object2`
that implement the interface. The factory object registers two creator functions in `object.cpp`:

```cpp
bool b1 = Singleton<ObjectFactory>::Instance().registercreator(object_type::OBJECT1, &object1_creator_fcn);
bool b2 = Singleton<ObjectFactory>::Instance().registercreator(object_type::OBJECT2, &object2_creator_fcn);
```

In the `main.cpp` we create concrete objects of type `object_type::OBJECT1` and `object_type::OBJECT2` as follows:

```cpp
object_ptr obj1, obj2;
obj1 = Singleton<ObjectFactory>::Instance().createobject(object_type::OBJECT1);
obj2 = Singleton<ObjectFactory>::Instance().createobject(object_type::OBJECT2);
```

When the `factory` library is loaded, `ObjectFactory` registers the
creator functions, and these can be used for generating objects of type `Object1` and `Object2`.
Functionality has been tested using both g++ version 9.4.0 and Visual Studio 2019.

## Main

An executable called `main` links against the `factory` library, and creates an object of `Object1` type and an
object of `Object2` type using a factory singleton-object from the `factory`. After this types of each of the objects are 
printed to the screen.

## DLL-support

In Visual C++ we need to export/import the instance of `Singleton<ObjectFactory>`, explicitly instantiated in [object.cpp](object.cpp), so
that this instance is used in the executable (main). If we don't do this, and call `Singleton<ObjectFactory>::Instance()` from the main, 
the `ObjectFactory` in the `main` and the `factory` library are different, and the instance in the `main` won't have any creator-functions registered.
In order to fix this problem in Visual C++, the explicitly instantiated Singleton template for the `FactoryObject` must be exported/imported as
static-objects are unique only within a compilation unit:

```cpp
template class FACTORY_EXPORT Singleton< Factory<object_ptr, object_id, createobject_fcn> >;
```

In `dll_support.hpp` we have the following macros for exporting and importing definitions:

```cpp
#if defined(_WIN32) && defined(FACTORY_DLL)
#    ifdef FACTORY_BUILD
//       Compiling a Windows DLL
#        define FACTORY_EXPORT __declspec(dllexport)
#    else
//       Using a Windows DLL
#        define FACTORY_EXPORT __declspec(dllimport)
#    endif
// Windows or Linux static library, or Linux so
#else
#    define FACTORY_EXPORT
#endif
```

This is not required in g++ as the symbols from the `factory` are exported by default.

## Incorporate Into a CMAKE Based Project

If you want to incorporate this library into your CMAKE-based project, you can use CMAKE's [FetchContant](https://cmake.org/cmake/help/latest/module/FetchContent.html)
in your build scripts as follows:

```cmake
FetchContent_Declare(
  factory
  GIT_REPOSITORY https://github.com/JarnoRalli/factory-pattern
  GIT_TAG        v2.0.0)

FetchContent_MakeAvailable(factory)

target_link_library(<MY-TARGET> factory::factory)
```
