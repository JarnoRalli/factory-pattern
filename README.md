# A Factory Pattern and a Singleton

This repository implements a simple factory-pattern and a singleton in a library called `factory`.

## Singleton
The singleton can be used for creating a single instance of a concrete factory. 
The singleton doesn't have constructors, so objects of this type cannot be created. Intended use
is calling the static function `Instance()` that returns a reference to a static object of type
`<T>`, e.g. `Singleton<Object>::Instance()`. An explicit instantiation of the Singleton template
must be exported from the library using `__declspec(dllexport)` in Visual Studio, otherwise the
the returned static-object is not truly 'singular' as each compilation unit will have its own
static-object.

## Factory

This repository implements a factory-pattern template that can be instantiated to created objects
that share a base-class. Creator-functions, that create the actual objects identified by an id,
are registered in a `std::map` inside a concrete factory-object. Functionality of the factory-pattern 
is showcased using an interface called `IObject`, and two object-classes called `Object1` and `Object2`
that implement the interface. The factory object registers two creator functions in `object.cpp`:

```cpp
bool b1 = Singleton<ObjectFactory>::Instance().registercreator(object_id::OBJECT1, &object1_creator_fcn);
bool b2 = Singleton<ObjectFactory>::Instance().registercreator(object_id::OBJECT2, &object2_creator_fcn);
```

When the `factory` library is loaded, `ObjectFactory` registers the
creator functions, and these can be used for generating objects of type `Object1` and `Object2`.
Functionality has been tested using both g++ version 9.4.0 and Visual Studio 2019.

## Main

An executable called `main` links against the `factory` library, and creates an object of `Object1` type and an
object of `Object2` type using a factory singleton-object from the `factory`. After this types of each of the objects are 
printed to the screen.

## DLL-support

In Visual Studio we have the problem that if we don't explicitly export/import the instance `Singleton<ObjectFactory>` from the
`factory` library, then when we call `Singleton<ObjectFactory>::Instance()` from the main, the `ObjectFactory` in the `main` and
the `factory` library are different and the instance in `main` doesn't have any creator-functions registered. In order to fix
this problem in Visual Studio, the explicitly instantiated Singleton template for the `FactoryObject` must be exported/imported as
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
