#pragma once

serial_port_stream::serial_port_stream ( )
    extends std::iostream ( nullptr )
{
    rdbuf(buff_ptr.get());
    exceptions(std::ios::badbit);
}

serial_port_stream::serial_port_stream ( string serial_port )
    extends std::iostream ( nullptr )
{
    rdbuf(buff_ptr.get());
    exceptions(std::ios::badbit);
    open(std::move(serial_port));
}

serial_port_stream::serial_port_stream ( serial_port_stream&& init )
    extends std::iostream ( std::move(static_cast<std::iostream&>(init)) )
{
    self.rdbuf(buff_ptr.get());

    std::swap(self.buff_ptr, init.buff_ptr);
    let self_rdbuf = self.rdbuf();
    let init_rdbuf = init.rdbuf();
    self.rdbuf(init_rdbuf);
    init.rdbuf(self_rdbuf);
}

serial_port_stream::~serial_port_stream ( )
{
    exceptions(std::ios::iostate());
}

serial_port_stream& serial_port_stream::operator = ( serial_port_stream&& right )
{
    self.std::iostream::operator=(std::move(static_cast<std::iostream&>(right)));

    std::swap(self.buff_ptr, right.buff_ptr);
    let self_rdbuf  = self .rdbuf();
    let right_rdbuf = right.rdbuf();
    self .rdbuf(right_rdbuf);
    right.rdbuf(self_rdbuf );

    return self;
}

serial_port_stream& serial_port_stream::open ( string serial_port )
{
    static_cast<serial_port_buf*>(rdbuf())->open(std::move(serial_port));
    return self;
}
serial_port_stream& serial_port_stream::close ( )
{
    static_cast<serial_port_buf*>(rdbuf())->close();
    clear();
    return self;
}

bool serial_port_stream::is_open ( ) const
{
    return static_cast<const serial_port_buf*>(rdbuf())->is_open();
}

