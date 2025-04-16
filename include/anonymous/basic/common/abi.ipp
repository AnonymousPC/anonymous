#pragma once

std::string demangle ( const std::type_info& t )
{
    auto ok  = 0;
    auto str = abi::__cxa_demangle(t.name(), nullptr, nullptr, &ok);

    auto std_str = (ok == 0) ? std::string(str) : std::string(t.name());
    free(str);
    return std_str;
} 
