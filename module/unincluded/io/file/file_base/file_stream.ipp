struct file_stream::read_only  extends public detail::io_mode<bool> { using detail::io_mode<bool>::io_mode; struct file_mode_tag { }; };
struct file_stream::write_only extends public detail::io_mode<bool> { using detail::io_mode<bool>::io_mode; struct file_mode_tag { }; };
struct file_stream::erase      extends public detail::io_mode<bool> { using detail::io_mode<bool>::io_mode; struct file_mode_tag { }; };
struct file_stream::append     extends public detail::io_mode<bool> { using detail::io_mode<bool>::io_mode; struct file_mode_tag { }; };

file_stream::file_stream ( path pth, file_mode auto... args )
{
    exceptions(std::ios::badbit);
    open(pth, std::forward<decltype(args)>(args)...);
}

#undef in
file_stream& file_stream::open ( path pth, file_mode auto... args )
{
    // Open.
    if constexpr ( sizeof...(args) == 0 )
        std::fstream::open(pth.c_str(), std::ios::in | std::ios::out | std::ios::binary);
    else
    {
        auto open_mode = std::ios_base::openmode();

        open_mode |= detail::value_of_same_type_or<read_only >(args..., read_only ()).value ? std::ios::in    : std::ios_base::openmode();
        open_mode |= detail::value_of_same_type_or<write_only>(args..., write_only()).value ? std::ios::out   : std::ios_base::openmode();
        open_mode |= detail::value_of_same_type_or<erase     >(args..., erase     ()).value ? std::ios::trunc : std::ios_base::openmode();
        open_mode |= detail::value_of_same_type_or<append    >(args..., append    ()).value ? std::ios::app   : std::ios_base::openmode();

        if ( open_mode & std::ios::in and open_mode & std::ios::out )
            throw file_error("conflicting settings: read_only == true and write_only == true");
        if ( open_mode & std::ios::trunc and open_mode & std::ios::app )
            throw file_error("conflicting settings: erase == true and append == true");

        if ( not ( open_mode & std::ios::in ) and not ( open_mode & std::ios::out ) ) // Default as both read and write.
            open_mode |= ( std::ios::in | std::ios::out );
        if ( open_mode == std::ios::out ) // Single write-only means override from the beginning.
            open_mode |= std::ios::in;

        std::fstream::open(pth.c_str(), open_mode);
    }

    // Exception.
    if ( not std::fstream::good() )
        throw file_error("cannot open file {}", pth);

    return self;
}
#define in :
