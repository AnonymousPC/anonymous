#pragma once

#ifdef __NVCC__
    class cuda
        extends public cpu
    {
        public: // Available
            constexpr static bool is_available ( ) { return true; }

        public: // Context
            using  execution_context_type = nvexec::stream_context;
            static execution_context_type execution_context;

        public: // Layout
            using layout_type = std::layout_left;

        public: // Allocator
            template < class type > using allocator = thrust::allocator<type>;

        public: // Compare
            template < class type = void > struct equal_to      { __host__ __device__ constexpr bool operator() (const auto& a, const auto& b) { return a == b; } };
            template < class type = void > struct not_equal_to  { __host__ __device__ constexpr bool operator() (const auto& a, const auto& b) { return a != b; } };
            template < class type = void > struct less          { __host__ __device__ constexpr bool operator() (const auto& a, const auto& b) { return a <  b; } };
            template < class type = void > struct less_equal    { __host__ __device__ constexpr bool operator() (const auto& a, const auto& b) { return a <= b; } };
            template < class type = void > struct greater       { __host__ __device__ constexpr bool operator() (const auto& a, const auto& b) { return a >  b; } };
            template < class type = void > struct greater_equal { __host__ __device__ constexpr bool operator() (const auto& a, const auto& b) { return a >= b; } };

        public: // Container
            template < class type, class alloc = allocator<type> > using vector = thrust::device_vector<type,alloc>;

        public: // Algorithm
            constexpr __host__ __device__ decltype(auto) copy          ( auto&&... args ) { return thrust::copy         (std::forward<decltype(args)>(args)...); }
            constexpr __host__ __device__ decltype(auto) copy_n        ( auto&&... args ) { return thrust::copy_n       (std::forward<decltype(args)>(args)...); }
            constexpr __host__ __device__ decltype(auto) copy_backward ( auto&&... args ) { return thrust::copy_backward(std::forward<decltype(args)>(args)...); }
            constexpr __host__ __device__ decltype(auto) move          ( auto&&... args ) { return thrust::move         (std::forward<decltype(args)>(args)...); }
            constexpr __host__ __device__ decltype(auto) move_backward ( auto&&... args ) { return thrust::move_backward(std::forward<decltype(args)>(args)...); }

    };
    cuda::execution_context_type cuda::execution_context = cuda::execution_context_type();
#else
    class cuda
        extends public cpu 
    {
        public: // Available
            constexpr static bool is_available ( ) { return false; }
    };
#endif