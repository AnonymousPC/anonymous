#pragma once

class stock_data
    extends public matrix<float>
{
    private: // Data
        path                     file_path  = "";
        flat_map<time_point,int> date_map   = {};
        flat_map<string,int>     option_map = {};

    public: // Open.
        stock_data& open ( );

    public: // Interface
        using matrix<float>::matrix;
        using matrix<float>::operator[];
        const float& operator [] ( const time_point&, const string_view& ) const;
        const auto dates   ( ) const;
        const auto options ( ) const;

    public: // Friend
        friend database;
};

class database
    extends public flat_map<string,stock_data>
{
    public: // Open
        database ( ) = default;
        database ( const char* );
        database ( path );
        database& open ( path );

    public: // Interface
        const stock_data& operator [] ( const string_view& ) const;
};


#if dll
    #include "database.cpp"
#endif