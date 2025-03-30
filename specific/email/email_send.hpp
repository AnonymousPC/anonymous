#pragma once

template < class type >
concept email_mode = requires { typename type::email_mode_tag; };

class email_send 
{
    public: // Constructor
        email_send ( email_mode auto... );

    public: // Modes
        struct server;
        struct username;
        struct password;
        struct from;
        struct to;
        struct cc;
        struct bcc;
        struct title;
        struct data;
        struct attachment;
};  

#include "email_send.ipp"