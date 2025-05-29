template < class container, class type, class device >
class string_interface
{
    private: // Typedef
        using value_type      = device::template value_type     <type>;
        using reference       = device::template reference      <type>;
        using const_reference = device::template const_reference<type>;
        using pointer         = device::template pointer        <type>;
        using const_pointer   = device::template const_pointer  <type>;

    private: // Abbreviation
        constexpr auto             begin           ( );
        constexpr auto             begin           ( )                                         const;
        constexpr auto             end             ( );
        constexpr auto             end             ( )                                         const;
        constexpr auto             data            ( );
        constexpr auto             data            ( )                                         const;
        constexpr auto             size            ( )                                         const;
        constexpr auto             empty           ( )                                         const;
        constexpr auto             operator []     ( int );
        constexpr auto             operator []     ( int )                                     const; 
    
    public: // Member
        constexpr bool             is_ascii        ( )                                         const;
        constexpr bool             is_print        ( )                                         const;
        constexpr bool             is_alnum        ( )                                         const;
        constexpr bool             is_alpha        ( )                                         const;
        constexpr bool             is_lower        ( )                                         const;
        constexpr bool             is_upper        ( )                                         const;
        constexpr bool             is_digit        ( )                                         const;
        constexpr bool             is_space        ( )                                         const;
        constexpr bool             is_blank        ( )                                         const;
        constexpr bool             is_punct        ( )                                         const;
        constexpr bool             is_cntrl        ( )                                         const;
        constexpr bool             is_title        ( )                                         const;

        constexpr container&       lower           ( );
        constexpr container&       upper           ( );
        constexpr container&       swap_case       ( );
        constexpr container&       capitalize      ( );
        constexpr container&       title           ( );
        constexpr container&       expand_tabs     ( int = 8 );
        constexpr container&       encode          ( std::text_encoding, std::text_encoding );

        constexpr bool             begins_with     ( const container& )                        const;
        constexpr bool             ends_with       ( const container& )                        const;
        constexpr container&       center          ( int,  type = ' ' );
        constexpr container&       left_justify    ( int,  type = ' ' );
        constexpr container&       right_justify   ( int,  type = ' ' );
        constexpr container&       strip           ( const type = ' ' );
        constexpr container&       left_strip      ( const type = ' ' );
        constexpr container&       right_strip     ( const type = ' ' );

        constexpr container&       join            ( const array<container>& );
        constexpr array<container> partition       ( const container& )                        const;
        constexpr array<container> split           ( const container& = ' ' )                  const;

        constexpr container&       format          ( std::formattable<type> auto&&... );

    public: // Member
        constexpr bool             contains        ( const container& )                                              const;
        constexpr int              count           ( const container& )                                              const;
        constexpr bool             exist           ( const container& )                                              const;
        constexpr int              find            ( const container& )                                              const;
        constexpr bool             none            ( const container& )                                              const;
        constexpr container&       remove          ( const container& );
        constexpr container&       replace         ( const container&, const container& );
        constexpr array<int>       where           ( const container& )                                              const;
};