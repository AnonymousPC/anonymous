#pragma once

/// Class pipe_stream

// Core

pipe_stream::pipe_stream ( path pth, pipe_mode auto... args )
    extends std::iostream ( nullptr )
{
    // Initialize.
    rdbuf(buff_ptr.get());

    // Set exception cases.
    exceptions(std::ios::badbit);

    // Connect.
    open(std::move(pth), std::forward<decltype(args)>(args)... );
}

// Interface

void pipe_stream::open ( path pth, pipe_mode auto... args )
{
    // Connect.
    let ptr = dynamic_cast<pipe_buf*>(rdbuf());
    if ( ptr != nullptr )
        ptr->open(std::move(pth), std::forward<decltype(args)>(args)...);
    else
        throw pipe_error("pipe_stream.rdbuf() does not points to a pipe_buf (with common = {}, current = {}, expected = {})",
                         typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(pipe_buf));
}