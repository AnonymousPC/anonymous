#pragma once

class ipv4
    extends public tuple<int,int,int,int,int>
{
    public: // Core
        ipv4 ( ) = default;
        ipv4 ( int, int, int, int );
        ipv4 ( int, int, int, int, int );

    public: // Parse
              int& first  ( );
        const int& first  ( ) const;
              int& second ( );
        const int& second ( ) const;
              int& third  ( );
        const int& third  ( ) const;
              int& fourth ( );
        const int& fourth ( ) const;
              int& port   ( );
        const int& port   ( ) const;
};


std::ostream& operator << ( std::ostream&, const ipv4& );



#if dll
    #include "ipv4.cpp"
#endif // dll