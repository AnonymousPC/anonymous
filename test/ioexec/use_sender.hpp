struct use_sender_t
    {
        constexpr use_sender_t() {}

        template <class InnerExecutor>
        struct executor_with_default : InnerExecutor
        {
            using default_completion_token_type = use_sender_t;

            executor_with_default(const InnerExecutor &ex) noexcept : InnerExecutor(ex) {}

            template <class _InnerExecutor>
                requires(!std::is_same_v<_InnerExecutor, executor_with_default> && std::is_convertible_v<_InnerExecutor, InnerExecutor>)
            executor_with_default(const _InnerExecutor &ex) noexcept : InnerExecutor(ex)
            {
            }
        };

        template <class T>
        using as_default_on_t = typename T::template rebind_executor<
            executor_with_default<typename T::executor_type>>::other;

        template <class T>
        static typename std::decay_t<T>::template rebind_executor<
            executor_with_default<typename std::decay_t<T>::executor_type>>::other
        as_default_on(T &&obj)
        {
            return typename std::decay_t<T>::template rebind_executor<
                executor_with_default<typename std::decay_t<T>::executor_type>>::other(std::forward<T>(obj));
        }
    };

    inline constexpr use_sender_t use_sender{};