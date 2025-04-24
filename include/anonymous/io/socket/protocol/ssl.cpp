ssl::endpoint ssl::socket::local_endpoint ( ) const
{
    return self.next_layer().local_endpoint();
}

ssl::endpoint ssl::socket::remote_endpoint ( ) const
{
    return self.next_layer().remote_endpoint();
}