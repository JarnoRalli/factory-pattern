#include "object.hpp"
#include "singleton.hpp"

int main(int argc, char* argv[])
{
    std::cout << "--- ENTERING MAIN ---" << std::endl;
    std::cout << "Nr registered creators from object.cpp: " << get_registered_creators() << std::endl;
    std::cout << "Nr registered creators from main: " << Singleton<ObjectFactory>::Instance().registered_creators.size() << std::endl;
    
    std::cout << "--- EXITING MAIN ---" << std::endl;
    return 0;
}