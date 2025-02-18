#pragma once

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
        struct text;
        struct attachment;
};  

#include "email_send.ipp"