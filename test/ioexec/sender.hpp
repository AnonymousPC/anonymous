template <class... Args>
        struct __sender
        {
            using sender_concept = __ex::sender_t;
            using completion_signatures = __ex::completion_signatures<
                __ex::set_value_t(Args...),
                __ex::set_error_t(std::exception_ptr),
                __ex::set_stopped_t()>;
            __initializer<Args...> _init;

            template <__ex::receiver R>
            struct __operation_base : __op_base<Args...>
            {
                using __storage_t = std::variant<
                    __initializer<Args...>,
                    __sbo_buffer<512, 64>>;

                __storage_t _storage;
                R _r;

                __operation_base(__initializer<Args...> &&i, R &&r) : _storage{std::move(i)}, _r{std::move(r)}
                {
                }

                __initializer<Args...> &__get_initializer() noexcept
                {
                    return std::get<0>(_storage);
                }

                __sbo_buffer<512, 64> &__emplace_buffer() noexcept
                {
                    return _storage.template emplace<1>();
                }

                void __stop() noexcept
                {
                    __ex::set_stopped(std::move(_r));
                }

                void __error() noexcept
                {
                    __ex::set_error(std::move(_r), std::current_exception());
                }

                void __init()
                {
                    auto initializer{std::move(__get_initializer())};
                    std::move(initializer)(use_sender_handler_base<Args...>{
                        .op{this},
                        .allocator{&__emplace_buffer()}});
                }

                void complete(Args... args) noexcept override
                {
                    const auto &res = std::tie(args...);
                    const auto &may_be_ec = __unwrap_first(res);
                    if constexpr (requires { may_be_ec == std::errc::operation_canceled; })
                    {
                        if (may_be_ec == std::errc::operation_canceled)
                        {
                            __stop();
                            return;
                        }
                    }
                    __ex::set_value(std::move(_r), std::move(args)...);
                }
            };

            template <__ex::receiver R>
            struct __operation final : __operation_base<R>
            {
                __operation(__initializer<Args...> &&i, R &&r)
                    : __operation_base<R>(std::move(i), std::move(r))
                {
                }

                enum struct __state_t : char
                {
                    construction,
                    emplaced,
                    initiated,
                    stopped
                };

                __io::cancellation_signal _signal{};
                std::atomic<__state_t> _state{__state_t::construction};

                struct __stop_t
                {
                    __operation *self;
                    void operator()() noexcept
                    {
                        __state_t expected = self->_state.load(std::memory_order_relaxed);
                        while (!self->_state.compare_exchange_weak(expected, __state_t::stopped, std::memory_order_acq_rel))
                        {
                        }
                        if (expected == __state_t::initiated)
                        {
                            self->_signal.emit(__io::cancellation_type_t::total);
                        }
                    }
                };

                using __stop_callback_t = typename __ex::stop_token_of_t<__ex::env_of_t<R> &>::template callback_type<__stop_t>;
                std::optional<__stop_callback_t> _stop_callback{};

                void __init()
                {
                    auto initializer{std::move(this->__get_initializer())};
                    std::move(initializer)(use_sender_handler<Args...>{
                        {.op{this},
                         .allocator{&this->__emplace_buffer()}},
                        _signal.slot()});
                }

                void complete(Args... args) noexcept override
                {
                    _stop_callback.reset();
                    __operation_base<R>::complete(std::move(args)...);
                }

                void start() & noexcept
                {
                    const auto st = __ex::get_stop_token(__ex::get_env(this->_r));
                    if (st.stop_requested())
                    {
                        this->__stop();
                        return;
                    }
                    _stop_callback.emplace(st, __stop_t{this});
                    __state_t expected = __state_t::construction;
                    if (!_state.compare_exchange_strong(expected, __state_t::emplaced, std::memory_order_acq_rel))
                    {
                        _stop_callback.reset();
                        this->__stop();
                        return;
                    }
                    // 初始化IO
                    try
                    {
                        __init();
                    }
                    catch (...)
                    {
                        _stop_callback.reset();
                        __error();
                        return;
                    }
                    // 如果没有请求取消，self._state == __state_t::emplaced
                    expected = __state_t::emplaced;
                    if (!_state.compare_exchange_strong(expected, __state_t::initiated, std::memory_order_acq_rel))
                    {
                        // 已经请求取消，但stop_callback不会发出取消信号（见__stop_t的if分支）
                        _stop_callback.reset();
                        _signal.emit(__io::cancellation_type_t::total);
                        return;
                    }
                }
            };

            template <__ex::receiver R>
            struct __asio_op_without_cancellation final : __operation_base<R>
            {
                __asio_op_without_cancellation(__initializer<Args...> &&i, R &&r)
                    : __operation_base<R>(std::move(i), std::move(r))
                {
                }

                void start() & noexcept
                {
                    try
                    {
                        this->__init();
                    }
                    catch (...)
                    {
                        this->__error();
                    }
                }
            };

            struct __transfer_sender
            {
                using sender_concept = __ex::sender_t;
                using completion_signatures = __ex::completion_signatures<
                    __ex::set_value_t(Args...),
                    __ex::set_error_t(std::exception_ptr),
                    __ex::set_stopped_t()>;

                __initializer<Args...> _init;

                template <__ex::receiver R>
                struct __transfer_op_without_cancellation final : __operation_base<R>
                {
                    __transfer_op_without_cancellation(__initializer<Args...> &&i, R &&r)
                        : __operation_base<R>(std::move(i), std::move(r))
                    {
                    }

                    void start() & noexcept
                    {
                        try
                        {
                            this->__init();
                        }
                        catch (...)
                        {
                            this->__error();
                        }
                    }
                };

                template <class Self, __ex::receiver R>
                __ex::operation_state auto connect(this Self &&self, R &&r)
                {
                    if constexpr (__ex::unstoppable_token<__ex::stop_token_of_t<__ex::env_of_t<R>>>)
                    {
                        return __transfer_op_without_cancellation<std::decay_t<R>>(
                            std::move(self._init),
                            std::forward<R>(r));
                    }
                    else
                    {
                        return __operation<std::decay_t<R>>(
                            std::move(self._init),
                            std::forward<R>(r));
                    }
                }
            };

            template <class Self, __ex::receiver R>
            __ex::operation_state auto connect(this Self &&self, R &&r)
            {
                auto env = __ex::get_env(r);
                if constexpr (requires { __ex::get_scheduler(env); })
                {
                    return __ex::connect(
                        __ex::continues_on(__transfer_sender{._init{std::move(self._init)}}, __ex::get_scheduler(env)),
                        std::forward<R>(r));
                }
                else
                {
                    if constexpr (__ex::unstoppable_token<__ex::stop_token_of_t<__ex::env_of_t<R>>>)
                    {
                        return __asio_op_without_cancellation<std::decay_t<R>>(
                            std::move(self._init),
                            std::forward<R>(r));
                    }
                    else
                    {
                        return __operation<std::decay_t<R>>(
                            std::move(self._init),
                            std::forward<R>(r));
                    }
                }
            }

        }; // __sender