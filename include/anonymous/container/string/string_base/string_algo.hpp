template < class container,
           class type,
           class device
         >
class string_algo
{
    private: // Typedef
        using value_type      = device::template value_type     <type>;
        using reference       = device::template reference      <type>;
        using const_reference = device::template const_reference<type>;
        using pointer         = device::template pointer        <type>;
        using const_pointer   = device::template const_pointer  <type>;

    private: // Abbreviation
        constexpr decltype(auto)   begin           ( );
        constexpr decltype(auto)   begin           ( )                                                               const;
        constexpr decltype(auto)   end             ( );
        constexpr decltype(auto)   end             ( )                                                               const;
        constexpr decltype(auto)   data            ( );
        constexpr decltype(auto)   data            ( )                                                               const;
        constexpr decltype(auto)   size            ( )                                                               const;
        constexpr decltype(auto)   empty           ( )                                                               const;
        constexpr decltype(auto)   operator []     ( int );
        constexpr decltype(auto)   operator []     ( int )                                                           const; 
    
    public: // String algo
        constexpr bool             begins_with     ( const container& )                                              const;
        constexpr bool             ends_with       ( const container& )                                              const;

        constexpr bool             is_alnum        ( )                                                               const;
        constexpr bool             is_alpha        ( )                                                               const;
        constexpr bool             is_ascii        ( )                                                               const;
        constexpr bool             is_blank        ( )                                                               const;
        constexpr bool             is_cntrl        ( )                                                               const;
        constexpr bool             is_digit        ( )                                                               const;
        constexpr bool             is_lower        ( )                                                               const;
        constexpr bool             is_punct        ( )                                                               const;
        constexpr bool             is_space        ( )                                                               const;
        constexpr bool             is_title        ( )                                                               const;
        constexpr bool             is_upper        ( )                                                               const;

        constexpr container&       lower           ( );
        constexpr container&       upper           ( );
        constexpr container&       swap_case       ( );

        constexpr container&       capitalize      ( );
        constexpr container&       title           ( );
        constexpr container&       expand_tabs     ( int = 8 );

        constexpr container&       center          ( int, type = ' ' );
        constexpr container&       left_justify    ( int, type = ' ' );
        constexpr container&       right_justify   ( int, type = ' ' );

        constexpr array<container> partition       ( const container& )                                              const;
        constexpr array<container> right_partition ( const container& )                                              const;

        constexpr array<container> split           ( const container& = ' ', int = std::numeric_limits<int>::max() ) const;
        constexpr array<container> right_split     ( const container& = ' ', int = std::numeric_limits<int>::max() ) const;
        constexpr array<container> split_lines     ( )                                                               const;

        constexpr container&       strip           ( const container& = ' ' );
        constexpr container&       left_strip      ( const container& = ' ' );
        constexpr container&       right_strip     ( const container& = ' ' );

        constexpr container&       encode          ( std::text_encoding, std::text_encoding )                              requires same_as<type,char> and same_as<device,cpu> ;
        constexpr container&       format          ( auto&&... f )                                                         requires same_as<type,char> and same_as<device,cpu> and ( ( formattable<decay<decltype(f)>> or constructible_from<container,decay<decltype(f)>> ) and ... );
        constexpr container&       join            ( auto&&... j )                                                         requires same_as<type,char> and same_as<device,cpu> and ( convertible_to<decay<decltype(j)>,container> and ... )

    public: // Array
        constexpr bool             contains        ( const container& )                                              const;
        constexpr int              count           ( const container& )                                              const;
        constexpr bool             exist           ( const container& )                                              const;
        constexpr int              find            ( const container& )                                              const;
        constexpr bool             none            ( const container& )                                              const;
        constexpr container&       remove          ( const container& );
        constexpr container&       replace         ( const container&, const container& );
        constexpr int              right_find      ( const container& )                                              const;
        constexpr array<int>       where           ( const container& )                                              const;
                            
    public: // Regex
        constexpr bool             all             ( const std::basic_regex<type>& )                                 const requires same_as<device,cpu>;
        constexpr bool             contains        ( const std::basic_regex<type>& )                                 const requires same_as<device,cpu>;
        constexpr int              count           ( const std::basic_regex<type>& )                                 const requires same_as<device,cpu>;
        constexpr bool             exist           ( const std::basic_regex<type>& )                                 const requires same_as<device,cpu>;
        constexpr int              find            ( const std::basic_regex<type>& )                                 const requires same_as<device,cpu>;
        constexpr bool             match           ( const std::basic_regex<type>& )                                 const requires same_as<device,cpu>;
        constexpr bool             none            ( const std::basic_regex<type>& )                                 const requires same_as<device,cpu>;
        constexpr container&       remove          ( const std::basic_regex<type>& )                                       requires same_as<device,cpu>;
        constexpr container&       replace         ( const std::basic_regex<type>&, const container& )                     requires same_as<device,cpu>;
        constexpr int              right_find      ( const std::basic_regex<type>& )                                 const requires same_as<device,cpu>;
        constexpr array<container> split           ( const std::basic_regex<type>& )                                 const requires same_as<device,cpu>;
        constexpr array<int>       where           ( const std::basic_regex<type>& )                                 const requires same_as<device,cpu>;
};