#pragma once

/// Class ipv4

// Core

ipv4::ipv4 ( int init_1, int init_2, int init_3, int init_4 )
    extends ipv4 ( init_1, init_2, init_3, init_4, 0 )
{

}

ipv4::ipv4 ( int init_1, int init_2, int init_3, int init_4, int init_port )
    extends tuple<int,int,int,int,int> ( init_1, init_2, init_3, init_4, init_port )
{
    if ( self.first () < 0 or self.first () > 255 or
         self.second() < 0 or self.second() > 255 or
         self.third () < 0 or self.third () > 255 or
         self.fourth() < 0 or self.fourth() > 255 or
         self.port  () < 0 or self.port  () > 65535 )
        throw network_error("ipv4 {} is invalid (example: 192.168.1.1:80)", self);
}

// Parse

int& ipv4::first ( )
{
    return self.template value<1>();
}

const int& ipv4::first ( ) const
{
    return self.template value<1>();
}

int& ipv4::second ( )
{
    return self.template value<2>();
}

const int& ipv4::second ( ) const
{
    return self.template value<2>();
}

int& ipv4::third ( )
{
    return self.template value<3>();
}

const int& ipv4::third ( ) const
{
    return self.template value<3>();
}

int& ipv4::fourth ( )
{
    return self.template value<4>();
}

const int& ipv4::fourth ( ) const
{
    return self.template value<4>();
}

int& ipv4::port ( )
{
    return self.template value<5>();
}

const int& ipv4::port ( ) const
{
    return self.template value<5>();
}




std::ostream& operator << ( std::ostream& left, const ipv4& right )
{
    return left << "{}.{}.{}.{}:{}"s.format(right.first(), right.second(), right.third(), right.fourth(), right.port());
}
