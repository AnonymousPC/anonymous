template < class type, class device >
class detail::tuple_upper<type,1,device>
{
    public: // Data
        std::vector<detail::array_upper<type,1,device>> vct;

    public: // Access
        template < auto attr, int dim2 > constexpr       std::span<detail::array_upper<type,dim2,device>> value ( const auto&, const int_type auto&... );
        template < auto attr, int dim2 > constexpr const std::span<detail::array_upper<type,dim2,device>> value ( const auto&, const int_type auto&... ) const;

    public: // Member
                               constexpr tuple_upper& clear  ( );
        template < auto attr > constexpr tuple_upper& resize ( const auto&, array<type,2,device>& );
        template < auto attr > constexpr tuple_upper& resize ( const auto&, std::vector<detail::array_upper<type,2,device>>& );  
};