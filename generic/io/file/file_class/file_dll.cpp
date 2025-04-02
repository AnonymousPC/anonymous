#pragma once

file_dll& file_dll::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.
    let dll = boost::dll::shared_library(pth.c_str());
    let tmp = boost::dll::library_info(pth.c_str()).symbols()
        | std::views::transform([&] (const auto& symbol) -> optional<pair<string,void*>>
            {
                try
                {
                    return pair(string(symbol.c_str()), dll.template get<void*>(symbol)); 
                }
                catch ( ... )
                {
                    return nullopt;
                }
            })
        | std::views::filter([] (const auto& kv) { return not kv.empty(); })
        | std::views::transform([] (const auto& kv) { return kv.value(); })
        | std::ranges::to<map<string,void*>>();

    static_cast<map<string,void*>&>(self) = tmp;

    return self;
        
}