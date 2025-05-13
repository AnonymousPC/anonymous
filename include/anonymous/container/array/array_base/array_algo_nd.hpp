template < class container,
           class type,
           int   dim,
           class device
         >
    requires ( dim >= 2 )
class array_algo<container,type,dim,device>
{
    private: // Typedef
        using value_type      = device::template value_type     <type>;
        using reference       = device::template reference      <type>;
        using const_reference = device::template const_reference<type>;
        using pointer         = device::template pointer        <type>;
        using const_pointer   = device::template const_pointer  <type>;

    private: // Abbreviation
        constexpr auto begin      ( );
        constexpr auto begin      ( ) const;
        constexpr auto end        ( );
        constexpr auto end        ( ) const;
        constexpr auto shape      ( ) const;
        constexpr auto empty      ( ) const;
        constexpr auto transpose  ( );
        constexpr auto transpose  ( ) const;

    public: // Member
        template < int axis > constexpr container&               reverse ( )           requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) );
        template < int axis > constexpr container&               rotate  ( int )       requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) );
        template < int axis > constexpr array<type,dim-1,device> average ( )     const requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) ) and default_initializable<type> and plusable<type> and dividable_to<type,int>;
        template < int axis > constexpr array<type,dim-1,device> sum     ( )     const requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) ) and default_initializable<type> and plusable<type>;
};