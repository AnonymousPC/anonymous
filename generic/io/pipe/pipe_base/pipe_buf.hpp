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
        /* boost::process::v2::process will immediate start once been constructed, so wrap it in unique_ptr */
        std::unique_ptr<boost::process::v2::process> handle      = nullptr;
        boost::asio::io_context                      ctx         = boost::asio::io_context();
        boost::asio::writable_pipe                   stdin_pipe  = boost::asio::writable_pipe(ctx);
        boost::asio::readable_pipe                   stdout_pipe = boost::asio::readable_pipe(ctx);
        boost::asio::readable_pipe                   stderr_pipe = boost::asio::readable_pipe(ctx);
        string                                       stdin_buff  = "";
        string                                       stdout_buff = "";
        string                                       stderr_buff = "";

    private: // Detail
        auto   run_with_args       ( const boost::filesystem::path&, std::vector<std::string>, const auto&, auto... );
        string process_id_noexcept ( ) const;

    private: // Typedef
        template < class... types > 
        struct tuple;

    private: // Settings
        constexpr static const int default_buffer_size = 4096;
};



#include "pipe_buf.ipp"
#if dll
    #include "pipe_buf.cpp"
#endif // dll