#pragma once

class pipe_buf
    extends public std::streambuf
{
    public: // Interface
        void open       ( path, pipe_mode auto... );
        void close      ( );
        bool is_open    ( ) const;
        bool is_running ( ) const;

    protected: // Interface (virtual)
        virtual int underflow ( )                          override;
        virtual int overflow  ( int = traits_type::eof() ) override;
        virtual int sync      ( )                          override;

    public: // Modes
        template < class type >
        struct mode_base;

        struct environment;
        struct param;
        struct start_directory;

    private: // Typedef
        struct mode_type;
        constexpr static const int default_buffer_size = 4096;

    public: // Data
        /* boost::process::v2::process will immediate start once been constructed */
        std::unique_ptr<boost::process::v2::process> process_handle = nullptr;
        boost::asio::writable_pipe                   stdin_pipe     = boost::asio::writable_pipe(io_context);
        boost::asio::readable_pipe                   stdout_pipe    = boost::asio::readable_pipe(io_context);
        boost::asio::readable_pipe                   stderr_pipe    = boost::asio::readable_pipe(io_context);
        string                                       stdin_buff     = "";
        string                                       stdout_buff    = "";
        string                                       stderr_buff    = "";

    private: // Auxiliary
        auto run_with_args ( const auto&, boost::filesystem::path, std::vector<std::string>, auto... );
        template < class... types > struct tuple;
};




/// Subclass


template < class type >
struct pipe_buf::mode_base
{
    type value = type();
    constexpr mode_base ( type );
};

template < array_type type >
struct pipe_buf::mode_base<type>
{
    type value = type();
    constexpr mode_base ( type::value_type );
    constexpr mode_base ( type::value_type, std::convertible_to<typename type::value_type> auto... );
    constexpr mode_base ( type );
};

template < map_type type >
struct pipe_buf::mode_base<type>
{
    type value = type();
    constexpr mode_base ( type::key_type /*string*/, type::value_type::value_type /*string*/       );
    constexpr mode_base ( type::key_type /*string*/, type::value_type             /*array<string>*/);
    constexpr mode_base ( pair<typename type::key_type,typename type::value_type::value_type> /*pair<string,string*/        );
    constexpr mode_base ( pair<typename type::key_type,typename type::value_type>             /*pair<string,array<string>>*/);
    constexpr mode_base ( map <typename type::key_type,typename type::value_type::value_type> /*map<string,string>*/        );
    constexpr mode_base ( map <typename type::key_type,typename type::value_type>             /*map<string,array<string>>*/ );
};

struct pipe_buf::environment     extends public pipe_buf::mode_base<map<string,array<string>>> { using mode_base::mode_base; struct pipe_mode_tag{}; };
struct pipe_buf::param           extends public pipe_buf::mode_base<array<string>>             { using mode_base::mode_base; struct pipe_mode_tag{}; };
struct pipe_buf::start_directory extends public pipe_buf::mode_base<path>                      { using mode_base::mode_base; struct pipe_mode_tag{}; };

#include "pipe_buf.ipp"
#if dll
    #include "pipe_buf.cpp"
#endif // dll