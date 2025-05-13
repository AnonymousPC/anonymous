namespace detail
{
    template < class base >
    class opencl_container
        extends private base
    {
        private: // Precondition
            static_assert(layout_compatible_with<base,boost::compute::vector<typename base::value_type>>, 
                          "only designed for containers who wraps and only wraps a boost::compute::vector");
        
        public: // Typedef
            using value_type      = base::value_type;
            using reference       = opencl::template reference      <value_type>;
            using const_reference = opencl::template const_reference<value_type>;
            using pointer         = opencl::template pointer        <value_type>;
            using const_pointer   = opencl::template const_pointer  <value_type>;
            using iterator        = pointer;
            using const_iterator  = const_pointer;

        public: // Core
            opencl_container ( );
            opencl_container ( const opencl_container&  );
            opencl_container (       opencl_container&& );
            opencl_container& operator = ( const opencl_container&  );
            opencl_container& operator = (       opencl_container&& );
            opencl_container ( auto&&... args ) requires       constructible_from<base,decltype(args)...,const boost::compute::context&>;
            opencl_container ( auto&&... args ) requires ( not constructible_from<base,decltype(args)...,const boost::compute::context&> ) and constructible_from<base,decltype(args)...,boost::compute::command_queue&>; 
        
        public: // Vector
            std::size_t       size          ( )           const;
            bool              empty         ( )           const;
            iterator          begin         ( );
            const_iterator    begin         ( )           const;
            iterator          end           ( );
            const_iterator    end           ( )           const;
            pointer           data          ( );
            const_pointer     data          ( )           const;
            reference         front         ( );
            const_reference   front         ( )           const;
            reference         back          ( );
            const_reference   back          ( )           const;
            reference         operator []   ( auto&&... );
            const_reference   operator []   ( auto&&... ) const;
            iterator          find          ( auto&&... );
            const_iterator    find          ( auto&&... ) const;
            std::size_t       count         ( auto&&... ) const;
            void              resize        ( auto&&... );
            void              reserve       ( auto&&... );
            void              shrink_to_fit ( auto&&... );
            void              clear         ( auto&&... );
            void              push_back     ( auto&&... );
            void              pop_back      ( auto&&... );
            auto              insert        ( auto&&... );
            auto              erase         ( auto&&... );

        public: // Set, Map
            iterator          lower_bound   ( auto&&... );
            const_iterator    lower_bound   ( auto&&... ) const;
            iterator          upper_bound   ( auto&&... );
            const_iterator    upper_bound   ( auto&&... ) const;
            
        public: // Stack
            reference         top           ( );
            const_reference   top           ( )           const;
            void              pop           ( );

        private: // Detail
                  boost::compute::vector<value_type>& as_vector ( );
            const boost::compute::vector<value_type>& as_vector ( ) const;
    };
    
} // namespace detail

#include "opencl_container.cpp"