template < class type, int dim, class device >
    requires ( dim >= 2 )
class detail::array_uppers<type,dim,device>
{
    public: // Data
        std::vector<detail::array_upper<type,dim,device>> vct;
        array_uppers<type,dim-1,device>                    vct_other;

    public: // Access
        template < auto attr, int dim2 > constexpr pair<      detail::array_upper<type,dim2,device>*> value ( const auto&, const integral auto&... );
        template < auto attr, int dim2 > constexpr pair<const detail::array_upper<type,dim2,device>*> value ( const auto&, const integral auto&... ) const; 

    public: // Member
                               constexpr array_uppers& clear  ( );
        template < auto attr > constexpr array_uppers& resize ( const auto&,                     array      <type,dim+1,device> & );
        template < auto attr > constexpr array_uppers& resize ( const auto&, std::vector<detail::array_upper<type,dim+1,device>>& );  
};