#pragma once

} // Out of namespace ap::asio

namespace boost::asio
{
    template < class... types > 
    class async_result<ap::asio::use_sender_t,void(types...)>
    {
        public: // Typedef
            using return_type = ap::asio::sender<types...>;

        public: // Interface
            static int initiate ( auto&&, ap::asio::use_sender_t, auto&&... );
    };

    template < class... types >
    int async_result<ap::asio::use_sender_t,void(types...)>::initiate ( auto&& initiation, ap::asio::use_sender_t, auto&&... args )
    {
        return return_type(std::forward<decltype(initiation)>(initiation), std::forward<decltype(args)>(args)...);
    }
    
} // namespace boost::asio

namespace ap::asio { // Back into namespace ap::asio

