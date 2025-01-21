#pragma once

std::string demangle ( const std::type_info& t )
{
    let ok  = 0;
    let str = ::abi::__cxa_demangle(t.name(), nullptr, nullptr, &ok);

    let std_str = (ok == 0) ? std::string(str) otherwise std::string(t.name());
    free(str);
    return std_str;
} 
