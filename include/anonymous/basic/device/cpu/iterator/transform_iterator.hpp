template < class iterator, class function >
class cpu::transform_iterator
{
    public: // Typedef
        using iterator_category = std::common_type_t<typename std::iterator_traits<iterator>::iterator_category,std::random_access_iterator_tag>;
        using value_type        = std::remove_cvref_t<std::invoke_result_t<function,typename std::iterator_traits<iterator>::value_type>>;
        using reference         = std::invoke_result_t<function,typename std::iterator_traits<iterator>::reference>;
        using difference_type   = std::iterator_traits<iterator>::difference_type;

    private: // Data
        iterator iter = iterator();
        function func = function();

    public: // Core
        constexpr transform_iterator ( )                    requires std::default_initializable<iterator> and std::default_initializable<function> = default;
        constexpr transform_iterator ( iterator )           requires std::default_initializable<function>;
        constexpr transform_iterator ( iterator, function );

    public: // Member
        constexpr reference operator *  ( )                 const;
        constexpr reference operator [] ( difference_type ) const requires std::random_access_iterator<iterator>;

    public: // Access
        constexpr iterator base      ( ) const;
        constexpr function transform ( ) const;
};
         