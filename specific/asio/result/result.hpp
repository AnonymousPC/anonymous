#pragma once

} // Out of namespace ap::asio

namespace boost::asio
{
    template < class... types > 
    class async_result<ap::asio::use_sender_t,types...>
    {
        public: // Typedef
            using return_type = ap::asio::sender<types...>;

        public: // Interface
            static int initiate ( auto&&, ap::asio::use_sender_t, types&&... );

            // static int initiate ( auto&&... args )
            // {
            //     typeid_buf = std::vector{&typeid(args)...};
            //     return 42;
            // }
    };

    template < class... types >
    int async_result<ap::asio::use_sender_t,types...>::initiate ( auto&& initiation, ap::asio::use_sender_t, types&&... args )
    {
        return return_type(std::forward<decltype(initiation)>(initiation), std::forward<decltype(args)>(args)...);
    }
    
} // namespace boost::asio

namespace ap::asio { // Back into namespace ap::asio

