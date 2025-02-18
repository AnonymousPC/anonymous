#pragma once

namespace detail
{
    string encode_base64 ( const string& );    

    // template < class range >
    // class base64_encoder
    //     extends public std::ranges::view_interface<base64_encoder>
    // {
    //     private:
    //         range r;
    //         int   v = 0; // Current value.
    //         int   b = 0; // Available bits, 8-bits per input char. When it becomes >= 6, a 6-bit base64-letter is available.

    //     public:
    //         constexpr base64_encoder ( range );

    //     public:
    //         struct iterator;

    //     public:
    //         constexpr auto begin ( ) const;
    //         constexpr auto end   ( ) const;
    //         constexpr auto size  ( ) const requires std::ranges::sized_range<range>;
    // };

    // struct base64_encoder::iterator 
    // {
    //     base64_encoder* ptr = nullptr;

    //     char operator* ( ) const;
        

    // };
}

#if dll
    #include "base64.cpp"
#endif