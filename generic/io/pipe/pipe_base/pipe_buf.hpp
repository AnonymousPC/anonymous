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
        struct environment;
        struct param;
        struct start_directory;

    private: // Typedef
        struct mode_type;
        template < class type > struct mode_base;
        constexpr static const int default_buffer_size = 4096;

    private: // Data
        /* boost::process::v2::process will immediate start once been constructed */
        /* boost::asio::io_context is not movable */
        std::unique_ptr<boost::process::v2::process> process_handle = nullptr;
        std::unique_ptr<boost::asio::io_context>     context_handle = std::make_unique<boost::asio::io_context>(2);
        boost::asio::writable_pipe                   stdin_pipe     = boost::asio::writable_pipe(*context_handle);
        boost::asio::readable_pipe                   stdout_pipe    = boost::asio::readable_pipe(*context_handle);
        boost::asio::readable_pipe                   stderr_pipe    = boost::asio::readable_pipe(*context_handle);
        string                                       stdin_buff     = "";
        string                                       stdout_buff    = "";
        string                                       stderr_buff    = "";

    private: // Auxiliary
        // This is not similiar to http_buf.set_request(field_1, ...), http_buf.set_request(field_2, ...),
        // as all params must be forwarded at one time.
        auto run_with_args ( const boost::filesystem::path&, std::vector<std::string>, const auto&, auto... );
        template < class... types > struct tuple;
};




/// Subclass


template < class type >
struct pipe_buf::mode_base
{
    type value = type();
    constexpr mode_base ( type );
    struct pipe_mode_tag { };
};

template < array_type type >
struct pipe_buf::mode_base<type>
{
    type value = type();
    constexpr mode_base ( type::value_type );
    constexpr mode_base ( type::value_type, std::convertible_to<typename type::value_type> auto... );
    constexpr mode_base ( type );
    struct pipe_mode_tag { };
};

template < map_type type > // map<string,array<string>>
struct pipe_buf::mode_base<type>
{
    type value = type();
    constexpr mode_base ( type::key_type /*string*/, type::value_type::value_type /*string*/       );
    constexpr mode_base ( type::key_type /*string*/, type::value_type             /*array<string>*/);
    constexpr mode_base ( pair<typename type::key_type,typename type::value_type::value_type> /*pair<string,string*/        );
    constexpr mode_base ( pair<typename type::key_type,typename type::value_type>             /*pair<string,array<string>>*/);
    constexpr mode_base ( map <typename type::key_type,typename type::value_type::value_type> /*map<string,string>*/        );
    constexpr mode_base ( type );
    struct pipe_mode_tag { };
};

struct pipe_buf::environment     extends public pipe_buf::mode_base<map<string,array<string>>> { using mode_base::mode_base; };
struct pipe_buf::param           extends public pipe_buf::mode_base<array<string>>             { using mode_base::mode_base; };
struct pipe_buf::start_directory extends public pipe_buf::mode_base<path>                      { using mode_base::mode_base; };

#include "pipe_buf.ipp"
#if dll
    #include "pipe_buf.cpp"
#endif // dll