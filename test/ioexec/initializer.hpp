template <class... Args>
        struct __initializer
        {
            using __any_t = basic_any<256, 16>;

        private:
            struct __init_base
            {
                virtual void init(use_sender_handler_base<Args...> &&) = 0;
                virtual void init(use_sender_handler<Args...> &&) = 0;
            };

            template <class Init, class... InitArgs>
            struct __init_impl final : __init_base
            {
                Init _init;
                std::tuple<InitArgs...> _args;

                template <class _Init, class... _InitArgs>
                __init_impl(_Init &&init, _InitArgs &&...args) : _init{std::forward<_Init>(init)},
                                                                 _args{std::forward<_InitArgs>(args)...}
                {
                }

                __init_impl(const __init_impl &) = delete;
                __init_impl &operator=(const __init_impl &) = delete;
                __init_impl(__init_impl &&) noexcept = default;
                __init_impl &operator=(__init_impl &&) noexcept = default;

                void init(use_sender_handler_base<Args...> &&handler) override
                {
                    ap::print(std::source_location::current().function_name());
                    ap::print();
                    std::apply(std::move(_init), std::tuple_cat(std::make_tuple(std::move(handler)), std::move(_args)));
                }

                void init(use_sender_handler<Args...> &&handler) override
                {
                    std::apply(std::move(_init), std::tuple_cat(std::make_tuple(std::move(handler)), std::move(_args)));
                }
            };

        public:
            template <class Init, class... InitArgs>
            __initializer(Init &&init, InitArgs &&...args)
            {
                _data = __init_impl<std::decay_t<Init>, std::decay_t<InitArgs>...>(std::forward<Init>(init), std::forward<InitArgs>(args)...);
            }

            template <class Init>
            __initializer(Init &&init)
            {
                _data = __init_impl<std::decay_t<Init>>(std::forward<Init>(init));
            }

            __initializer(const __initializer &) = delete;
            __initializer &operator=(const __initializer &) = delete;

            __initializer(__initializer &&other) noexcept : _data{std::move(other._data)}
            {
            }

            void operator()(use_sender_handler_base<Args...> &&handler)
            {
                unsafe_any_cast<__init_base>(&_data)->init(std::move(handler));
            }

            void operator()(use_sender_handler<Args...> &&handler)
            {
                unsafe_any_cast<__init_base>(&_data)->init(std::move(handler));
            }

        private:
            __any_t _data;
        };