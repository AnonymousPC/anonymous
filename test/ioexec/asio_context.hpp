
class asio_context
{
    friend struct __detail::scheduler_t;

public:
    using scheduler_t = __detail::scheduler_t;

    asio_context() : _self{std::in_place},
                     _ctx{*_self},
                     _guard{std::in_place, __io::make_work_guard(_ctx)}
    {
    }

    asio_context(__io::io_context &ctx) : _ctx{ctx}
    {
    }

    asio_context(const asio_context &) = delete;
    asio_context(asio_context &&) = delete;
    asio_context &operator=(const asio_context &) = delete;
    asio_context &operator=(asio_context &&) = delete;

    ~asio_context()
    {
        join();
    }

    void start()
    {
        _th = std::thread([this]
                          { _ctx.run(); });
    }

    void stop() noexcept
    {
        _guard.reset();
    }

    void join()
    {
        stop();
        if (_th.joinable())
            _th.join();
    }

    __detail::scheduler_t get_scheduler() noexcept;

    __io::io_context &get_executor() noexcept { return _ctx; }
    const __io::io_context &get_executor() const noexcept { return _ctx; }

private:
    std::optional<__io::io_context> _self{};
    __io::io_context &_ctx;
    std::optional<__io::executor_work_guard<__io::io_context::executor_type>> _guard{};
    std::thread _th{};
};