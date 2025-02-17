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
        struct title;
        struct data;

    private:
        struct mode_base;
};  

struct email_send::mode_base
{
    string value = "";
    mode_base ( string );
    struct email_mode_tag { };
};

struct email_send::server   extends public email_send::mode_base { using mode_base::mode_base; };
struct email_send::username extends public email_send::mode_base { using mode_base::mode_base; };
struct email_send::password extends public email_send::mode_base { using mode_base::mode_base; };
struct email_send::from     extends public email_send::mode_base { using mode_base::mode_base; };
struct email_send::to       extends public email_send::mode_base { using mode_base::mode_base; };
struct email_send::title    extends public email_send::mode_base { using mode_base::mode_base; };
struct email_send::data     extends public email_send::mode_base { using mode_base::mode_base; };

#include "email_send.ipp"
#if dll
    #include "email_send.cpp"
#endif