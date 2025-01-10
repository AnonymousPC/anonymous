#pragma once

namespace detail
{
    /* ABI of array (dim == 1)
     * device::vector     (sizeof = device::vector)
     * from_array_view
     *   - host_ptr       (sizeof = sizeof(pointer))
     */

    /* ABI of array (dim >= 2)
     * device::vector     (sizeof = device::vector)
     * from_array_view
     *   - host_ptr       (sizeof = sizeof(pointer))
     *   - transpose_ptr  (sizeof = sizeof(pointer))
     * to_array_view
     *   - row_views      (sizeof = device::vector)
     *   - column_views   (sizeof = device::vector)
     *   - flat_view      [[omitted, directly static_cast]]
     *   - transpose_view (sizeof = sizeof(pointer))
     */

    struct size_tag  { };
    struct shape_tag { };
    struct empty_tag { };
    struct begin_tag { };
    struct end_tag   { };
    struct index_tag { };

    template < class type >
    struct from_array_span;

    template < class type, class device >
    struct from_array_span<array<type,1,device>>
    {
        private:
            array<type,2,device>* host_ptr = nullptr;
    
        public:
            constexpr from_array_span ( ) = default;
            constexpr from_array_span ( array<type,2,device>* ptr ) extends host_ptr ( ptr ) { }

        public:
            constexpr       array<type,2,device>& from_host ( )       { return *host_ptr; }
            constexpr const array<type,2,device>& from_host ( ) const { return *host_ptr; }

        public: 
            constexpr bool is_span ( ) const { return host_ptr != nullptr; }
    };
    
    template < class type, int dim, class device >
        requires ( dim >= 2 )
    struct from_array_span<array<type,dim,device>>
    {
        private:
            array<type,dim+1,device>* host_ptr      = nullptr;
            array<type,dim,  device>* transpose_ptr = nullptr;

        public: 
            constexpr from_array_span ( ) = default;
            constexpr from_array_span ( array<type,dim+1,device>* ptr_1, array<type,dim,device>* ptr_2 ) extends host_ptr ( ptr_1 ), transpose_ptr ( ptr_2 ) { }

        public:
            constexpr       array<type,dim+1,device>& from_host      ( )       { return *host_ptr;      }
            constexpr const array<type,dim+1,device>& from_host      ( ) const { return *host_ptr;      }
            constexpr       array<type,dim,  device>& from_transpose ( )       { return *transpose_ptr; }
            constexpr const array<type,dim,  device>& from_transpose ( ) const { return *transpose_ptr; }

        public:
            constexpr bool is_view ( ) const { return host_ptr != nullptr or transpose_ptr != nullptr; }
    };

    template < class type > 
    struct to_array_view;

    template < class type, int dim, class device >
    struct to_array_view

    template < class type, class... types >
    constexpr bool ints_until_last_func = []
    {
        if constexpr ( is_void<type> )
            return convertible_until<int,-2,types...> and std::invocable<last_type_of<types...>>;
        else
            return convertible_until<int,-2,types...> and function_type<last_type_of<types...>,type()>;
    } ();

    template < class result_type, class input_type, int count, class... types >
    constexpr bool invocable_r_by_n_ints_helper = []
    {
        if constexpr ( count >= 1 )
            return invocable_r_by_n_ints_helper<result_type,input_type,count-1,int,types...>;
        else
            if constexpr ( is_void<result_type> )
                return std::invocable<input_type,types...>;
            else
                return function_type<input_type,result_type(types...)>;
    } ();

    template < class result_type, class input_type, int count >
    constexpr bool invocable_r_by_n_ints = invocable_r_by_n_ints_helper<result_type,input_type,count>;

    template < class type, class... types >
    constexpr bool ints_until_last_func_ints = convertible_until<int,-2,types...> and invocable_r_by_n_ints<type,last_type_of<types...>,sizeof...(types)-1>; // No need to check <void,...>, as it forwards to is_invocable_r_by_n_ints.

    template < class type, class... types >
    constexpr bool ints_until_last_type = convertible_until<int,-2,types...> and []
    {
        if constexpr ( is_void<type> )
            return not ints_until_last_func<type,types...> and not ints_until_last_func_ints<type,types...>;
        else
            return std::convertible_to<last_type_of<types...>,type>;
    } ();

    template < class input_type, int count, class... types >
    struct invoke_result_by_n_ints_helper;

    template < class input_type, int count, class... types >
        requires ( count >= 1 )
    struct invoke_result_by_n_ints_helper<input_type,count,types...>
    {
        using type = invoke_result_by_n_ints_helper<input_type,count-1,int,types...>::type;
    };

    template < class input_type, int count, class... types >
        requires ( count == 0 )
    struct invoke_result_by_n_ints_helper<input_type,count,types...>
    {
        using type = invoke_result<input_type,types...>;
    };

    template < class input_type, int count >
    using invoke_result_by_n_ints = invoke_result_by_n_ints_helper<input_type,count>::type; // Helper
}