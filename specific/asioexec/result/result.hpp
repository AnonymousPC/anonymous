#pragma once

} // Out of namespace ap::asioexec

namespace boost::asio
{
    template < class... types > 
    class async_result<ap::asioexec::use_sender_t,void(types...)>
    {
        public: // Interface
            static auto initiate ( auto&&, ap::asioexec::use_sender_t, auto&&... );

        public: // Typedef
            using return_type = decltype(initiate([] (auto&&...) {}, std::declval<ap::asioexec::use_sender_t>()));
    };

    template < class... types >
    auto async_result<ap::asioexec::use_sender_t,void(types...)>::initiate ( auto&& start_func, ap::asioexec::use_sender_t, auto&&... start_args )
    {
        let sched_sender = std::execution::read_env(std::execution::get_scheduler);
        let value_sender = std::execution::just(std::forward<decltype(start_func)>(start_func), std::forward<decltype(start_args)>(start_args)...);
        return std::execution::when_all(std::move(sched_sender), std::move(value_sender))
             | std::execution::let_value([] (auto&& sched, auto&&... args)
                 {
                     return ap::asioexec::sender<types...>(std::forward<decltype(args)>(args)...)
                          | std::execution::continues_on(std::forward<decltype(sched)>(sched));
                 });
                    
    }
    
} // namespace boost::asio

namespace ap::asioexec { // Back into namespace ap::asioexec

