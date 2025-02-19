#pragma once

template < class type >
concept pipe_mode = requires { typename type::pipe_mode_tag; };

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
        constexpr static const int default_buffer_size = 4096;
        // This is not similiar to http_buf.set_request(field_1, ...), http_buf.set_request(field_2, ...),
        // as all params must be forwarded at one time.
        auto run_with_args ( const boost::filesystem::path&, std::vector<std::string>, const auto&, auto... );
        template < class... types > struct tuple;
};



#include "pipe_buf.ipp"
#if dll
    #include "pipe_buf.cpp"
#endif // dll