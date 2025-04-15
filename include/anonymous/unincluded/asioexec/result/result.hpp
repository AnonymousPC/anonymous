#pragma once

} // Out of namespace anonymous::asioexec

namespace boost::asio
{
    template < class... types > 
    class async_result<anonymous::asioexec::use_sender_t,void(types...)>
    {
        public: // Interface
            static auto initiate ( auto&&, anonymous::asioexec::use_sender_t, auto&&... );

        public: // Typedef
            using return_type = decltype(initiate([] (auto&&...) {}, std::declval<anonymous::asioexec::use_sender_t>()));
    };

    template < class... types >
    auto async_result<anonymous::asioexec::use_sender_t,void(types...)>::initiate ( auto&& start_func, anonymous::asioexec::use_sender_t, auto&&... start_args )
    {
        let sched_sender = std::execution::read_env(std::execution::get_scheduler);
        let value_sender = std::execution::just(std::forward<decltype(start_func)>(start_func), std::forward<decltype(start_args)>(start_args)...);
        return std::execution::when_all(std::move(sched_sender), std::move(value_sender))
             | std::execution::let_value([] (auto&& sched, auto&&... args)
                 {
                     if constexpr ( anonymous::same_as<anonymous::decay<anonymous::first_type_of<types...>>,boost::system::error_code> )
                         return anonymous::asioexec::sender<types...>(std::forward<decltype(args)>(args)...)
                              | std::execution::let_value([] (boost::system::error_code ec, auto&&... args)
                                  {
                                      if ( ec )
                                          throw boost::system::system_error(ec);
                                      return std::execution::just(std::forward<delctype(args)>(args)...);
                                  })
                              | std::execution::continues_on(std::forward<decltype(sched)>(sched));
                     else
                          return anonymous::asioexec::sender<types...>(std::forward<decltype(args)>(args)...)
                               | std::execution::continues_on(std::forward<decltype(sched)>(sched));
                 });
                    
    }
    
} // namespace boost::asio

namespace anonymous::asioexec { // Back into namespace anonymous::asioexec

