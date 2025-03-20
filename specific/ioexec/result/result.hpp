#pragma once

} // Out of namespace ap::ioexec

namespace boost::asio
{
    template < class... types > 
    class async_result<ap::ioexec::use_sender_t,void(types...)>
    {
        public: // Typedef
            using return_type = ap::ioexec::sender<types...>;

        public: // Interface
            static return_type initiate ( auto&&, ap::ioexec::use_sender_t, auto&&... );
    };

    template < class... types >
    async_result<ap::ioexec::use_sender_t,void(types...)>::return_type async_result<ap::ioexec::use_sender_t,void(types...)>::initiate ( auto&& start_func, ap::ioexec::use_sender_t, auto&&... start_args )
    {
        return return_type(std::forward<decltype(start_func)>(start_func), std::forward<decltype(start_args)>(start_args)...);
    }
    
} // namespace boost::asio

namespace ap::ioexec { // Back into namespace ap::ioexec

