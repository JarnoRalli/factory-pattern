# A Factory Pattern with Singleton

This repository implements a simple factory-pattern and a singleton-object in a library called `factory`.
The singleton-object can be used for creating a single instance of a concrete factory. 
Functionality of the factory-pattern is showcased using an interface called `IObject`, 
and two object-classes called `Object1` and `Object2` that implement the interface.
The factory object registers two creator functions in `object.cpp`:

```cpp
bool b1 = Singleton<ObjectFactory>::Instance().registercreator(object_id::OBJECT1, &object1_creator_fcn);
bool b2 = Singleton<ObjectFactory>::Instance().registercreator(object_id::OBJECT2, &object2_creator_fcn);
```

When an executable, that links against the `factory` library, is loaded, `ObjectFactory` registers the
creator functions, and these can be used for generating objects of type `Object1` and `Object2`.
Functionality has been tested using both g++ version 9.4.0 and Visual Studio 2019.

