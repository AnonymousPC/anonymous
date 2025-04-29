template < class type1, class type2, class device >
class expected
    extends public device::template expected<type1,type2>
{
    private: // Precondition
        static_assert ( not is_void<type1> and not is_reference<type1> );
        static_assert ( not is_void<type2> and not is_reference<type2> );
        static_assert ( default_initializable<type1> );
        static_assert ( not same_as<type1,type2> );

    public: // Typedef
        using value_type            = device::template value_type           <type1>;
        using value_reference       = device::template reference            <type1>;
        using const_value_reference = device::template const_value_reference<type1>;
        using error_type            = device::template value_type           <type2>;
        using error_reference       = device::template reference            <type2>;
        using const_error_reference = device::template const_reference      <type2>;
        using device_type           = device;

    public: // Core
        constexpr expected ( )                                                                           = default;
        constexpr expected ( const expected&  )             requires copyable<type1> and copyable<type2> = default;
        constexpr expected (       expected&& )             requires movable <type1> and movable <type2> = default;
        constexpr expected& operator = ( const expected&  ) requires copyable<type1> and copyable<type2> = default;
        constexpr expected& operator = (       expected&& ) requires movable <type1> and movable <type2> = default;

    public: // Constructor
        constexpr expected ( type1 );
        constexpr expected ( type2 );

    public: // Member
        constexpr       value_reference       value ( );
        constexpr       const_value_reference value ( ) const;
        constexpr       error_reference       error ( );
        constexpr       const_error_reference error ( ) const;
        constexpr       int                   index ( ) const;
        constexpr const std::type_info&       type  ( ) const;
};

#include "expected.cpp"