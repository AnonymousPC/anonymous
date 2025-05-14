template < class type, class device >
class detail::array_uppers<type,1,device>
{
    public: // Data
        std::vector<detail::array_upper<type,1,device>> vct;

    public: // Access
        template < auto attr, int dim2 > constexpr pair<      detail::array_upper<type,dim2,device>*> value ( const auto&, const int_type auto&... );
        template < auto attr, int dim2 > constexpr pair<const detail::array_upper<type,dim2,device>*> value ( const auto&, const int_type auto&... ) const;

    public: // Member
                               constexpr array_uppers& clear  ( );
        template < auto attr > constexpr array_uppers& resize ( const auto&, array<type,2,device>& );
        template < auto attr > constexpr array_uppers& resize ( const auto&, std::vector<detail::array_upper<type,2,device>>& );  
};