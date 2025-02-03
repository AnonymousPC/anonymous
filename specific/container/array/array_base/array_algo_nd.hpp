#pragma once

template < class array_type,
           class type,
           int   dim,
           class device
         >
    requires ( dim >= 2 )
class array_algo<array_type,type,dim,device>
{
    private: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;

    private: // Abbreviation
        constexpr decltype(auto) begin      ( );
        constexpr decltype(auto) begin      ( ) const;
        constexpr decltype(auto) end        ( );
        constexpr decltype(auto) end        ( ) const;
        constexpr decltype(auto) data       ( );
        constexpr decltype(auto) data       ( ) const;
        constexpr decltype(auto) size       ( ) const;
        constexpr decltype(auto) shape      ( ) const;
        constexpr decltype(auto) empty      ( ) const;
        constexpr decltype(auto) ownership  ( ) const;
        constexpr decltype(auto) contiguous ( ) const;
        constexpr decltype(auto) transpose  ( );
        constexpr decltype(auto) transpose  ( ) const;

    public: // Member
        template < int axis > constexpr array_type&              reverse ( )           requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) );
        template < int axis > constexpr array_type&              rotate  ( int )       requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) );
        template < int axis > constexpr array<type,dim-1,device> average ( )     const requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) ) and default_initializable<type> and plusable<type> and dividable_to<type,int>;
        template < int axis > constexpr array<type,dim-1,device> sum     ( )     const requires ( ( axis >= -dim and axis <= -1 ) or ( axis >= 1 and axis <= dim ) ) and default_initializable<type> and plusable<type>;
};