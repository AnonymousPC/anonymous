/// Class pipe_stream

// Core

pipe_stream::pipe_stream ( path exe, pipe_mode auto... args )
    extends std::iostream ( nullptr )
{
    rdbuf(buff_ptr.get());
    exceptions(std::ios::badbit);
    open(std::move(exe), std::forward<decltype(args)>(args)...);
}

// Interface

pipe_stream& pipe_stream::open ( path exe, pipe_mode auto... args )
{
    static_cast<pipe_buf*>(rdbuf())->open(std::move(exe), std::forward<decltype(args)>(args)...);
    return self;
}