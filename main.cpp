#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
#include "dll.hpp"
using namespace ap;


int main ( )
{
    let info = boost::dll::library_info("dll.dylib");
    std::ranges::for_each(info.sections(), [&] (const auto& section)
        {
            print("<<{}>>"s.format(section));
            std::ranges::for_each(info.symbols(section), print);
            print("=====");
        });
    

};
