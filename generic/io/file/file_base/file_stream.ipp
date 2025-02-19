#pragma once

struct file_stream::read_only  extends public detail::io_mode<bool> { using detail::io_mode<bool>::io_mode; struct file_mode_tag { }; };
struct file_stream::write_only extends public detail::io_mode<bool> { using detail::io_mode<bool>::io_mode; struct file_mode_tag { }; };
struct file_stream::erase      extends public detail::io_mode<bool> { using detail::io_mode<bool>::io_mode; struct file_mode_tag { }; };
struct file_stream::append     extends public detail::io_mode<bool> { using detail::io_mode<bool>::io_mode; struct file_mode_tag { }; };


struct file_stream::mode_type
{
    bool read_only  = false;
    bool write_only = false;
    bool erase      = false;
    bool append     = false;
};

file_stream::file_stream ( path pth, file_mode auto... args )
{
    // Set exception cases.
    exceptions(std::ios::badbit);

    // Open
    open(pth, std::forward<decltype(args)>(args)...);
}

file_stream& file_stream::open ( path pth, file_mode auto... args )
{
    // Open.
    if constexpr ( sizeof...(args) == 0 )
        #undef in
        std::fstream::open(pth.c_str(), std::ios::in | std::ios::out | std::ios::binary);
        #define in :
    else
        std::fstream::open(pth.c_str(), make_std_openmode(make_mode(args...)));

    // Exception.
    if ( not std::fstream::good() )
        throw file_error("cannot open file {}", pth);

    return self;
}

file_stream::mode_type file_stream::make_mode ( auto prm, auto... args )
{
    // Check.
    static_assert(detail::all_different<decltype(prm),decltype(args)...>, "modes must be unique");
    return make_mode(mode_type(), prm, args...);
}

file_stream::mode_type file_stream::make_mode ( mode_type modes, auto prm, auto... args )
{
    // Set.
    if constexpr ( same_as<decltype(prm),read_only> )
        modes.read_only = prm.value;
    else if constexpr ( same_as<decltype(prm),write_only> )
        modes.write_only = prm.value;
    else if constexpr ( same_as<decltype(prm),erase> )
        modes.erase = prm.value;
    else if constexpr ( same_as<decltype(prm),append> )
        modes.append = prm.value;

    // Continue.
    if constexpr ( sizeof...(args) >= 1 )
        return make_mode(modes, args...);

    // Triggered iff the last mode is set.
    else if constexpr ( sizeof...(args) == 0 )
    {
        if ( modes.read_only and modes.write_only )
            throw file_error("conflicting settings: read_only == true and write_only == true");
        else if ( modes.erase and modes.append )
            throw file_error("conflicting settings: erase == true and append == true");

        return modes;
    }
}