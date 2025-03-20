template <class... Args>
        struct __op_base
        {
            __op_base() = default;
            __op_base(const __op_base &) = delete;
            __op_base(__op_base &&) = delete;
            __op_base &operator=(const __op_base &) = delete;
            __op_base &operator=(__op_base &&) = delete;
            virtual void complete(Args... args) noexcept {};
        };