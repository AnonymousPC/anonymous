template < class container, 
           class type,
           class device
         >
class collection_algo
{
    private: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;

    private: // Abbreviation
        constexpr decltype(auto) begin ( );
        constexpr decltype(auto) begin ( ) const;
        constexpr decltype(auto) end   ( );
        constexpr decltype(auto) end   ( ) const;
        constexpr decltype(auto) size  ( ) const;

    public: // Algorithm
        constexpr       auto       average  ( )                       const requires default_initializable<type> and plusable    <type> and dividable_to<type,int>;
        constexpr       auto       sum      ( )                       const requires default_initializable<type> and plusable    <type>;
        constexpr       auto       product  ( )                       const requires convertible_to<int,type>    and multipliable<type>;

        constexpr       container& for_each ( invocable<type&> auto );
        constexpr const container& for_each ( invocable<type>  auto ) const;
};


#include "collection_algo.cpp"