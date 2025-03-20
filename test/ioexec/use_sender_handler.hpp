template <class... Args>
        struct use_sender_handler_base
        {
            using allocator_type = std::pmr::polymorphic_allocator<>;

            __op_base<Args...> *op;
            allocator_type allocator;

            allocator_type get_allocator() const noexcept { return allocator; }

            template <class... _Args>
            void operator()(_Args &&...args)
            {
                op->complete(std::forward<_Args>(args)...);
            }
        };

        template <class... Args>
        struct use_sender_handler : use_sender_handler_base<Args...>
        {
            using cancellation_slot_type = __io::cancellation_slot;
            cancellation_slot_type slot;
            cancellation_slot_type get_cancellation_slot() const noexcept { return slot; }
        };