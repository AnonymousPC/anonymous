template <size_t Size = 64ull, size_t Alignment = 16>
        class __sbo_buffer final : public std::pmr::memory_resource
        {
        public:
            explicit __sbo_buffer(std::pmr::memory_resource *upstream = std::pmr::get_default_resource()) noexcept : _upstream{upstream}
            {
            }

            __sbo_buffer(const __sbo_buffer &) = delete;
            __sbo_buffer &operator=(const __sbo_buffer &) = delete;
            __sbo_buffer(__sbo_buffer &&) = delete;
            __sbo_buffer &operator=(__sbo_buffer &&) = delete;

        private:
            void *do_allocate(size_t bytes, size_t alignment) override
            {
                if (_used || bytes > Size || alignment > Alignment)
                {
                    assert(_upstream && "Upstream memory_resource is empty.");
                    return _upstream->allocate(bytes, alignment);
                }
                _used = true;
                return &_storage;
            }

            void do_deallocate(void *ptr, size_t bytes, size_t alignment) noexcept override
            {
                if (ptr == &_storage)
                {
                    _used = false;
                    return;
                }
                _upstream->deallocate(ptr, bytes, alignment);
            }

            bool do_is_equal(const std::pmr::memory_resource &other) const noexcept override
            {
                return this == std::addressof(other);
            }

        private:
            std::pmr::memory_resource *_upstream;
            bool _used = false;
            alignas(Alignment) unsigned char _storage[Size];
        };