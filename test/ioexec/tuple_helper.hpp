template <class T>
        concept __is_tuple = requires(T &&t) {
            std::get<0>(t);
        };

        template <class T>
        constexpr decltype(auto) __unwrap_first(T &&t) noexcept
        {
            return std::forward<T>(t);
        }

        template <__is_tuple T>
        constexpr decltype(auto) __unwrap_first(T &&t) noexcept
        {
            return __unwrap_first(std::get<0>(std::forward<T>(t)));
        }

        template <class T>
        using __unwrap_first_t = std::decay_t<decltype(__unwrap_first(std::declval<T>()))>;

        template <__is_tuple T>
        constexpr decltype(auto) __unwrap_tuple(T &&t) noexcept
        {
            if constexpr (std::tuple_size<T>{} == size_t(1))
            {
                return __unwrap_tuple(std::get<0>(std::forward<T>(t)));
            }
            else
            {
                return std::forward<T>(t);
            }
        }

        template <class T>
        constexpr decltype(auto) __unwrap_tuple(T &&t) noexcept
        {
            return std::make_tuple(std::forward<T>(t));
        }

        template <class _Fn>
            requires std::is_nothrow_move_constructible_v<_Fn>
        struct __conv
        {
            _Fn __fn_;
            using __t = std::invoke_result_t<_Fn>;

            operator __t() && noexcept(std::is_nothrow_invocable_v<_Fn>)
            {
                return ((_Fn &&)__fn_)();
            }

            __t operator()() && noexcept(std::is_nothrow_invocable_v<_Fn>)
            {
                return ((_Fn &&)__fn_)();
            }
        };

        template <class _Fn>
        __conv(_Fn) -> __conv<_Fn>;