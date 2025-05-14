template < class type, int dim, class device >
    requires ( dim >= 2 )
class detail::array_lower<type,dim,device>
{
    private: // Data
        array_uppers<type,dim-1,device> rows_view;
        array_uppers<type,dim-1,device> columns_view;
        array_upper <type,dim,  device> transpose_view;

    public: // Typedef
        using value_type      = device::template value_type      <type>;
        using reference       = device::template reference       <type>;
        using const_reference = device::template const_reference <type>;
        using pointer         = device::template pointer         <type>;
        using const_pointer   = device::template const_pointer   <type>;
        using iterator        = cpu   ::template transform_iterator<      detail::array_upper<type,dim-1,device>*,detail::to_array_pointer>;
        using const_iterator  = cpu   ::template transform_iterator<const detail::array_upper<type,dim-1,device>*,detail::to_array_pointer>;

    public: // Core
        constexpr array_lower ( );
        constexpr array_lower ( const array_lower&  ) = delete;
        constexpr array_lower (       array_lower&& ) = delete;

    public: // Member
        constexpr       iterator                  begin        ( );
        constexpr       const_iterator            begin        ( )     const;
        constexpr       iterator                  end          ( );
        constexpr       const_iterator            end          ( )     const;
        constexpr       array<type,dim-1,device>& operator []  ( int );
        constexpr const array<type,dim-1,device>& operator []  ( int ) const;

    public: // Member
        constexpr array_lower& clear ( );

    public: // View
        constexpr       array<type,dim,device>& transpose ( );
        constexpr const array<type,dim,device>& transpose ( ) const;

    public: // Detail
        template < int dim2 > constexpr pair<      detail::array_upper<type,dim2,device>*> get_rows    ( int_type auto... );
        template < int dim2 > constexpr pair<const detail::array_upper<type,dim2,device>*> get_rows    ( int_type auto... )         const; 
        template < int dim2 > constexpr pair<      detail::array_upper<type,dim2,device>*> get_columns ( int_type auto... );
        template < int dim2 > constexpr pair<const detail::array_upper<type,dim2,device>*> get_columns ( int_type auto... )         const;
                              constexpr void                                               set_resize  ( detail::array_shape<dim> );
};
