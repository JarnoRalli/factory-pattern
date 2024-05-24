#include "factory/object.hpp"
#include "factory/singleton.hpp"

int main(int argc, char* argv[])
{
    std::cout << "--- ENTERING MAIN ---" << std::endl;
    std::cout << "Nr registered creators from object.cpp: " << get_nr_registered_creators() << std::endl;
    std::cout << "Nr registered creators from main: " << Singleton<ObjectFactory>::Instance().registered_creators.size()
              << std::endl;

    object_ptr obj1, obj2;
    obj1 = Singleton<ObjectFactory>::Instance().createobject(object_type::OBJECT1);
    obj2 = Singleton<ObjectFactory>::Instance().createobject(object_type::OBJECT2);

    std::cout << "obj1 type: " << to_string(obj1->get_object_type()) << std::endl;
    std::cout << "obj2 type: " << to_string(obj2->get_object_type()) << std::endl;

    std::cout << "--- EXITING MAIN ---" << std::endl;
    return 0;
}