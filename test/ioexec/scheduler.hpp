struct scheduler_t
        {
            explicit scheduler_t(__io::io_context &ctx) noexcept : _ctx{&ctx}
            {
            }

            bool operator==(const scheduler_t &) const noexcept = default;

            auto schedule() const noexcept
            {
                return __schedule_sender_t{_ctx};
            }

        private:
            struct __schedule_sender_t
            {
                using sender_concept = __ex::sender_t;
                using completion_signatures = __ex::completion_signatures<
                    __ex::set_value_t(),
                    __ex::set_error_t(std::exception_ptr),
                    __ex::set_stopped_t()>;

                __io::io_context *_ctx;

                struct __env_t
                {
                    __io::io_context *_ctx;

                    template <class CPO>
                    scheduler_t query(__ex::get_completion_scheduler_t<CPO>) const noexcept
                    {
                        return scheduler_t{*_ctx};
                    }
                };

                template <__ex::receiver R>
                struct __op
                {
                    __io::io_context *_ctx;
                    R _r;

                    template <__ex::receiver _R>
                    __op(__io::io_context *ctx, _R &&r) noexcept : _ctx{ctx},
                                                                   _r{std::forward<_R>(r)}
                    {
                    }

                    __op(const __op &) = delete;
                    __op(__op &&) = delete;
                    __op &operator=(const __op &) = delete;
                    __op &operator=(__op &&) = delete;

                    struct __sched_task_t
                    {
                        __op *self;
                        using allocator_type = std::pmr::polymorphic_allocator<>;
                        allocator_type allocator;
                        allocator_type get_allocator() const noexcept { return allocator; }
                        void operator()() noexcept
                        {
                            __ex::set_value(std::move(self->_r));
                        }
                    };

                    __sbo_buffer<128> _buf{};

                    void start() & noexcept
                    {
                        if constexpr (!__ex::unstoppable_token<__ex::stop_token_of_t<__ex::env_of_t<R>>>)
                        {
                            const __ex::stoppable_token auto st = __ex::get_stop_token(__ex::get_env(_r));
                            if (st.stop_requested())
                            {
                                __ex::set_stopped(std::move(_r));
                                return;
                            }
                        }
                        try
                        {
                            __io::post(*_ctx, __sched_task_t{
                                                  .self{this},
                                                  .allocator{&_buf}});
                        }
                        catch (...)
                        {
                            __ex::set_error(std::move(_r), std::current_exception());
                        }
                    }
                };

                template <__ex::receiver R>
                auto connect(R &&r) noexcept
                {
                    return __op<std::decay_t<R>>{_ctx, std::forward<R>(r)};
                }

                auto query(__ex::get_env_t) const noexcept
                {
                    return __env_t{_ctx};
                }
            };

            static_assert(__ex::sender<__schedule_sender_t>);

            // 这个改成schedule函数以后一定要声明为public!!!!
            /*     friend auto tag_invoke(__ex::schedule_t, scheduler_t self)noexcept {
                    return __schedule_sender_t{ self._ctx };
                } */

            __io::io_context *_ctx;
        };