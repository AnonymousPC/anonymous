#pragma once

class url
    extends public string
{
    public: // Core
        using string::string;
        url ( string );

    public: // Parse
        string scheme        ( ) const;
        string authorization ( ) const;
        string host          ( ) const;
        string port          ( ) const;
        string path          ( ) const;
        string param         ( ) const;
        string fragment      ( ) const;

    public: // Regex
        static const ap::regex regex;
};


#if dll
    #include "url.cpp"
#endif