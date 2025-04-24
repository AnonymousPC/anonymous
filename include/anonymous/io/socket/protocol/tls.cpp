tls::endpoint tls::socket::local_endpoint ( ) const
{
    return self.next_layer().local_endpoint();
}

tls::endpoint tls::socket::remote_endpoint ( ) const
{
    return self.next_layer().remote_endpoint();
}