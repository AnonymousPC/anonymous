#pragma once

/// Class pipe_stream

// Close

pipe_stream::pipe_stream ( )
    extends std::iostream ( nullptr )
{
    // Initialize
    rdbuf(buff_ptr.get()); // Buff is contructed after std::iostream, so "extends std::iostream(&buff)" will cause segfault.

    // Set exception cases.
    exceptions(std::ios::badbit);
}

pipe_stream::pipe_stream ( pipe_stream&& init )
    extends std::iostream ( std::move(static_cast<std::iostream&>(init)) )
{
    self.rdbuf(buff_ptr.get());

    std::swap(self.buff_ptr, init.buff_ptr);
    let self_rdbuf = self.rdbuf();
    let init_rdbuf = init.rdbuf();
    self.rdbuf(init_rdbuf);
    init.rdbuf(self_rdbuf);
}

pipe_stream::~pipe_stream ( )
{
    // Reset exception cases.
    exceptions(std::ios::iostate());
}

pipe_stream& pipe_stream::operator = ( pipe_stream&& right )
{
    self.std::iostream::operator=(std::move(static_cast<std::iostream&>(right)));

    std::swap(self.buff_ptr, right.buff_ptr);
    let self_rdbuf  = self .rdbuf();
    let right_rdbuf = right.rdbuf();
    self .rdbuf(right_rdbuf);
    right.rdbuf(self_rdbuf );

    return self;
}

// Interface

void pipe_stream::close ( )
{
    let ptr = dynamic_cast<pipe_buf*>(rdbuf());
    if ( ptr != nullptr )
        ptr->close();
    else
        throw pipe_error("pipe_stream.rdbuf() does not point to a pipe_buf (with common = {}, current = {}, expected = {})",
                         typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(pipe_buf));

    clear();
}

bool pipe_stream::is_open ( ) const
{
    let ptr = dynamic_cast<pipe_buf*>(rdbuf());
    if ( ptr != nullptr )
        return ptr->is_open();
    else
        throw pipe_error("pipe_stream.rdbuf() does not point to a pipe_buf (with common = {}, current = {}, expected = {})",
                         typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(pipe_buf));
}

bool pipe_stream::is_running ( ) const
{
    let ptr = dynamic_cast<pipe_buf*>(rdbuf());
    if ( ptr != nullptr )
        return ptr->is_running();
    else
        throw pipe_error("pipe_stream.rdbuf() does not point to a pipe_buf (with common = {}, current = {}, expected = {})",
                         typeid(std::streambuf), ptr != nullptr ? typeid(*ptr) otherwise typeid(nullptr), typeid(pipe_buf));
}


// Override

std::ostream& pipe_stream::flush ( )
{
    if ( rdbuf() != nullptr )
    {
        std::ostream::sentry(self);
        let success = rdbuf()->pubsync(); // May throws pipe_error (instead of std::ios_base::failure).
        if ( success == -1 )
            setstate(std::ios::badbit);
    }

    return self;
}



