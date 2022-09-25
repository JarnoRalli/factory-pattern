#pragma once

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
