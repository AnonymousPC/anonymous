#pragma once

class ipv6
    extends public tuple<int,int,int,int,int,int,int,int,int>
{
    public: // Core
        ipv6 ( ) = default;
        ipv6 ( int, int, int, int, int, int, int, int );
        ipv6 ( int, int, int, int, int, int, int, int, int );

    public: // Parse
              int& first   ( );
        const int& first   ( ) const;
              int& second  ( );
        const int& second  ( ) const;
              int& third   ( );
        const int& third   ( ) const;
              int& fourth  ( );
        const int& fourth  ( ) const;
              int& fifth   ( );
        const int& fifth   ( ) const;
              int& sixth   ( );
        const int& sixth   ( ) const;
              int& seventh ( );
        const int& seventh ( ) const;
              int& eighth  ( );
        const int& eighth  ( ) const;
              int& port    ( );
        const int& port    ( ) const;

};


std::ostream& operator << ( std::ostream&, const ipv6& );



#if dll
    #include "ipv6.cpp"
#endif // dll