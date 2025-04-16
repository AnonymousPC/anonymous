#pragma once

file_dll& file_dll::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.



    boost::dll::shared_library::load(pth.c_str());
    static_cast<unordered_map<string,file_dll_any>&>(self)
        = boost::dll::library_info(pth.c_str()).symbols()
        | std::views::transform([&] (const std::string& symbol)
            {
                auto dmg_symbol = boost::dll::detail::demangle_symbol(mangled_symbol.c_str());
                if ( dmg_symbol == "" )
                    dmg_symbol = symbol;

                return pair(string(dmg_symbol), file_dll_any(library, dmg_symbol));
            })
        | std::ranges::to<unordered_map<string,file_dll_any>>();

    return self;       
}

file_dll& file_dll::close ( )
{
    // Close file.
    file_interface::close();

    // Clear data.
    boost::dll::shared_library::unload();
    unordered_map<string,file_dll_any>::clear();

    return self;
}

file_dll_any& file_dll::operator [] ( const string& k )
{
    auto it = unordered_map<string,file_dll_any>::find(k);
    if ( it != unordered_map<string,file_dll_any>::end() )
        return get<1>(*it);
    else
        throw key_error("key {} not found", k);
}

const file_dll_any& file_dll::operator [] ( const string& k ) const
{
    return unordered_map<string,file_dll_any>::operator[](k);
}
