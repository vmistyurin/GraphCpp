#include <sstream>
#include <thread>

#include "core/utils/system_info.hpp"

namespace 
{
    std::string compiler_info()
    {
        std::stringstream result;

        #if defined(_MSC_VER)
            result << "MSVC " << _MSC_FULL_VER;
        #elif defined(__clang__)
            result << "Clang " << __clang_major__ << '.' << __clang_minor__ << "." << __clang_patchlevel__;
        #elif defined(__GNUC__)
            result << "GCC " << __GNUC__ << '.' << __GNUC_MINOR__ << '.' << __GNUC_PATCHLEVEL__;
        #elif
            result << "Unknown compiler";
        #endif

        return result.str();
    }

    std::string build_type()
    {
        #if defined(NDEBUG)
            return "Release";
        #else	
            return "Debug";
        #endif
    }

    std::string architecture()
    {
        #if defined(_M_X64) || defined(__LP64__)
            return "x64";
        #elif defined(_M_IX86) || defined(__i386__)
            return "x86";
        #elif
            return "unknown architecture"
        #endif
    }

    std::string stdlib()
    {
        #if defined(_LIBCPP_VERSION)
            return "libc++";
        #elif defined(__GLIBCXX__)
            return "libstdc++";
        #elif defined(_MSC_VER)
            return "msftl"; //https://twitter.com/MalwareMinigun/status/1024873776071159808
        #elif 
            return "unknown library";
        #endif
    }

    std::string operating_system() 
    {
        #if defined(_WIN32)
            return "Windows";
        #elif defined(__linux__)
            return "Linux";
        #elif defined(__APPLE__)
            return "macOS/iOS";
        #elif
            return "Unknown system";
        #endif
    }
}

unsigned int graphcpp::number_of_threads()
{
    return std::thread::hardware_concurrency();
}

std::string graphcpp::system_info()
{
    return "Builded with " + compiler_info() +
        " in " + build_type() + " mode" +
        " on " + operating_system() + " " + architecture() +
        " with " + stdlib() + "," +
        " will use " + std::to_string(number_of_threads()) + " threads";
}
