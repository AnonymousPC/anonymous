#pragma once

/// Class ipv6

// Core

ipv6::ipv6 ( int init_1, int init_2, int init_3, int init_4, int init_5, int init_6, int init_7, int init_8 )
    extends ipv6 ( init_1, init_2, init_3, init_4, init_5, init_6, init_7, init_8, 0 )
{

}

ipv6::ipv6 ( int init_1, int init_2, int init_3, int init_4, int init_5, int init_6, int init_7, int init_8, int init_port )
    extends tuple<int,int,int,int,int,int,int,int,int> ( init_1, init_2, init_3, init_4, init_5, init_6, init_7, init_8, init_port )
{
    if ( self.first  () < 0 or self.first  () > 255 or
         self.second () < 0 or self.second () > 255 or
         self.third  () < 0 or self.third  () > 255 or
         self.fourth () < 0 or self.fourth () > 255 or
         self.fifth  () < 0 or self.fifth  () > 255 or
         self.sixth  () < 0 or self.sixth  () > 255 or
         self.seventh() < 0 or self.seventh() > 255 or
         self.eighth () < 0 or self.eighth () > 255 or
         self.port   () < 0 or self.port   () > 65535 )
        throw network_error("ipv6 {} does not matches ipv6 domain (example: [fe80::1a2b:3c4d:5e6f:7g8h]:80)", self);
}

// Parse

int& ipv6::first ( )
{
    return self.template value<1>();
}

const int& ipv6::first ( ) const
{
    return self.template value<1>();
}

int& ipv6::second ( )
{
    return self.template value<2>();
}

const int& ipv6::second ( ) const
{
    return self.template value<2>();
}

int& ipv6::third ( )
{
    return self.template value<3>();
}

const int& ipv6::third ( ) const
{
    return self.template value<3>();
}

int& ipv6::fourth ( )
{
    return self.template value<4>();
}

const int& ipv6::fourth ( ) const
{
    return self.template value<4>();
}

int& ipv6::fifth ( )
{
    return self.template value<5>();
}

const int& ipv6::fifth ( ) const
{
    return self.template value<5>();
}

int& ipv6::sixth ( )
{
    return self.template value<6>();
}

const int& ipv6::sixth ( ) const
{
    return self.template value<6>();
}

int& ipv6::seventh ( )
{
    return self.template value<7>();
}

const int& ipv6::seventh ( ) const
{
    return self.template value<7>();
}

int& ipv6::eighth ( )
{
    return self.template value<8>();
}

const int& ipv6::eighth ( ) const
{
    return self.template value<8>();
}

int& ipv6::port ( )
{
    return self.template value<9>();
}

const int& ipv6::port ( ) const
{
    return self.template value<9>();
}





std::ostream& operator << ( std::ostream& left, const ipv6& right )
{ 
    return left << "[{}:{}:{}:{}:{}:{}:{}:{}]:{}"s.format(right.first(), right.second(), right.third(), right.fourth(), right.fifth(), right.sixth(), right.seventh(), right.eighth(), right.port());
}
