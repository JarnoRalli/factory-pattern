# A Factory Pattern with Singleton

This repo implements a simple factory-pattern and a singleton. A singleton of the factory registers two creator functions in `object.cpp`:

```cpp
bool b1 = Singleton<ObjectFactory>::Instance().registercreator(object_id::OBJECT1, &object1_creator);
bool b2 = Singleton<ObjectFactory>::Instance().registercreator(object_id::OBJECT2, &object2_creator);
```

Even though the singleton should create only a single instance of the factory, this does not appear to be the case.

## Output When Executing in Windows 11

Compiled with: Visual Studio 2019

```bash
Factory constructor, this: 98754C0
Factory registering a product-creator function
Factory registering a product-creator function
--- ENTERING MAIN ---
Nr registered creators from object.cpp: 2
Nr registered creators from main: Factory constructor, this: EFCA3450
0
--- EXITING MAIN ---
Factory destructor, this: EFCA3450
Factory destructor, this: 98754C0
```

As can be seen from the above, there are actually two instances of the factory, even if only one should ever exist.

## Output When Executing in Ubuntu 20.04

Compiled with: g++ version 9.4.0

```bash
Factory constructor, this: 13ED7160
Factory registering a product-creator function
Factory registering a product-creator function
--- ENTERING MAIN ---
Nr registered creators from object.cpp: 2
Nr registered creators from main: 2
--- EXITING MAIN ---
Factory destructor, this: 13ED7160
```

As can be seen from the above, there only exists a single instance of the factory, as expected.

