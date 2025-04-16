#pragma once

/// Class pipe_stream

// Close

pipe_stream::pipe_stream ( )
    extends std::iostream ( nullptr )
{
    rdbuf(buff_ptr.get());
    exceptions(std::ios::badbit);
}

pipe_stream::pipe_stream ( pipe_stream&& init )
    extends std::iostream ( std::move(static_cast<std::iostream&>(init)) )
{
    self.rdbuf(buff_ptr.get());

    std::swap(self.buff_ptr, init.buff_ptr);
    auto self_rdbuf = self.rdbuf();
    auto init_rdbuf = init.rdbuf();
    self.rdbuf(init_rdbuf);
    init.rdbuf(self_rdbuf);
}

pipe_stream::~pipe_stream ( )
{
    exceptions(std::ios::iostate());
}

pipe_stream& pipe_stream::operator = ( pipe_stream&& right )
{
    self.std::iostream::operator=(std::move(static_cast<std::iostream&>(right)));

    std::swap(self.buff_ptr, right.buff_ptr);
    auto self_rdbuf  = self .rdbuf();
    auto right_rdbuf = right.rdbuf();
    self .rdbuf(right_rdbuf);
    right.rdbuf(self_rdbuf );

    return self;
}

// Interface

pipe_stream& pipe_stream::close ( )
{
    static_cast<pipe_buf*>(rdbuf())->close();
    clear();
    return self;
}

bool pipe_stream::is_open ( ) const
{
    return static_cast<const pipe_buf*>(rdbuf())->is_open();
}

bool pipe_stream::is_running ( ) const
{
    return static_cast<const pipe_buf*>(rdbuf())->is_running();
}




