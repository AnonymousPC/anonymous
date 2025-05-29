namespace detail
{
    template < class type, class device >
    class char_category
    {
        public:
            constexpr static bool is_ascii      ( const type& );
            constexpr static bool is_print      ( const type& );
            constexpr static bool is_alnum      ( const type& );
            constexpr static bool is_alpha      ( const type& );
            constexpr static bool is_upper      ( const type& );
            constexpr static bool is_lower      ( const type& );
            constexpr static bool is_digit      ( const type& );
            constexpr static bool is_space      ( const type& );
            constexpr static bool is_blank      ( const type& );
            constexpr static bool is_punct      ( const type& );
            constexpr static bool is_cntrl      ( const type& );
            constexpr static bool is_title      ( const type&, const type& );

            constexpr static void upper         ( type& );
            constexpr static void lower         ( type& );
            constexpr static void swap_case     ( type& );

            constexpr static bool equal_to      ( const type&, const type& );
            constexpr static bool not_equal_to  ( const type&, const type& );
            constexpr static bool less_equal    ( const type&, const type& );
            constexpr static bool greater_equal ( const type&, const type& );

            constexpr static void title         ( type&, type& );

            constexpr static invocable_r<bool(type)> auto not_equal_to_func ( const type& );
    }; 
    
} // namespace detail

#include "char_category.cpp"
