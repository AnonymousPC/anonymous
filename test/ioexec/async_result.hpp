template <class... Args>
    struct async_result<asio2exec::use_sender_t, void(Args...)>
    {
        using return_type = asio2exec::sender<Args...>;

        template <class Initiation, class... InitArgs>
        static return_type initiate(
            Initiation &&init,
            asio2exec::use_sender_t,
            InitArgs &&...args)
        {
            return return_type{asio2exec::__detail::__initializer<Args...>(
                std::forward<Initiation>(init),
                std::forward<InitArgs>(args)...)};
        }
    };