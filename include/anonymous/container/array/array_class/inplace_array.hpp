template < class type, int len, class device >
class inplace_array
    extends public device::template inplace_vector<type,len>,
            public array_algo<inplace_array<type,len,device>,type,1,device>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> ); // Does not requires movable.
        static_assert ( len >= 1 );

    private: // Typedef
        using base = device::template inplace_vector<type,len>;

    public: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;
        using  iterator        = pointer;
        using  const_iterator  = const_pointer;
        using  device_type     = device;
        struct array_concept { };

    public: // Core
        constexpr inplace_array ( )                                                           = default;
        constexpr inplace_array ( const inplace_array&  )             requires copyable<type> = default;
        constexpr inplace_array (       inplace_array&& )             requires movable <type> = default;
        constexpr inplace_array& operator = ( const inplace_array&  ) requires copyable<type> = default;
        constexpr inplace_array& operator = (       inplace_array&& ) requires movable <type> = default;

    public: // Constructor
        constexpr explicit inplace_array ( int );
        constexpr          inplace_array ( int, const type& )                   requires copyable<type>;
        constexpr          inplace_array ( int, invocable_r<type>     auto ) requires movable <type>;
        constexpr          inplace_array ( int, invocable_r<type,int> auto ) requires movable <type>;
        constexpr          inplace_array ( std::initializer_list<type> )        requires copyable<type>;
        constexpr          inplace_array ( range<type> )                        requires copyable<type>;

    public: // Conversion
        template < class type2,           class device2 > constexpr inplace_array ( const array        <type2,1,   device2>& ) requires ( same_as<type,type2> or same_as<device,device2> ) and convertible_to<type2,type> and ( same_as<device,device2> or same_as<device,cpu> or same_as<device2,cpu> );
        template < class type2, int len2, class device2 > constexpr inplace_array ( const inplace_array<type2,len2,device2>& ) requires ( same_as<type,type2> or same_as<device,device2> ) and convertible_to<type2,type> and ( same_as<device,device2> or same_as<device,cpu> or same_as<device2,cpu> );
        template < class type2, int len2, class device2 > constexpr inplace_array ( const static_array <type2,len2,device2>& ) requires ( same_as<type,type2> or same_as<device,device2> ) and convertible_to<type2,type> and ( same_as<device,device2> or same_as<device,cpu> or same_as<device2,cpu> ) and ( len2 <= len );

    public: // Memebr
        constexpr static int                  dimension     ( );
        constexpr        int                  size          ( )     const;
        constexpr static int                  capacity      ( );
        constexpr        static_array<int,1>  shape         ( )     const;
        constexpr        int                  row           ( )     const = delete;
        constexpr        int                  column        ( )     const = delete;
        constexpr        bool                 empty         ( )     const;
        constexpr        pointer              data          ( );
        constexpr        const_pointer        data          ( )     const;
        constexpr        iterator             begin         ( );
        constexpr        const_iterator       begin         ( )     const;
        constexpr        iterator             end           ( );
        constexpr        const_iterator       end           ( )     const;
        constexpr        reference            operator []   ( int );
        constexpr        const_reference      operator []   ( int ) const;

    public: // Member
        constexpr inplace_array& clear  ( );
        constexpr inplace_array& resize ( int );
        constexpr inplace_array& push   ( type )      requires movable<type>;
        constexpr inplace_array& pop    ( int = -1 )  requires movable<type>;
        constexpr inplace_array& insert ( int, type ) requires movable<type>;
        constexpr inplace_array& erase  ( int, int )  requires movable<type>;

    public: // View
        constexpr       array<type,1,device>& flatten   ( )       = delete;
        constexpr const array<type,1,device>& flatten   ( ) const = delete;
        constexpr       array<type,1,device>& transpose ( )       = delete;
        constexpr const array<type,1,device>& transpose ( ) const = delete;

    public: // Memory
        constexpr static bool ownership  ( );
        constexpr static bool contiguous ( );

    public: // Mdspan
        constexpr       auto mdspan ( );
        constexpr const auto mdspan ( ) const;

    private: // Friend
        template < class type2, int dim2, class device2 > friend class array;
        template < class type2, int len2, class device2 > friend class inplace_array;
        template < class type2, int len2, class device2 > friend class static_array;
};