#pragma once

file_dll& file_dll::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.
    let dll = boost::dll::shared_library(pth.c_str());
    static_cast<map<string,void*>&>(self)
        = boost::dll::library_info(pth.c_str()).symbols()
        | std::views::transform([&] (const auto& symbol) 
            {
                return pair(symbol.c_str(), dll.template get<void*>(symbol)); 
            })
        | std::ranges::to<map<string,void*>>();

    return self;
        
}