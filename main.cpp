#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
#include "dll.hpp"
using namespace ap;

std::string my_demangle ( std::string mangle )
{
    let ok  = 0;
    let str = abi::__cxa_demangle(mangle.c_str(), nullptr, nullptr, &ok);

    let std_str = (ok == 0) ? std::string(str) otherwise std::string(mangle);
    free(str);
    return std_str;
}

int main ( )
{
    let dllinfo = boost::dll::library_info("dll.dylib");
    std::ranges::for_each(dllinfo.sections(), [&] (const auto& section)
        {
            print("<<{}>>"s.format(section));
            std::ranges::for_each(dllinfo.symbols(section), print);
            print("=====");
        });

    let dll = boost::dll::shared_library("dll.dylib");
    dll.template get<void(*)(std::string)>("hello_world")("hello");
    
    
};

