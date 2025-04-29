namespace detail
{
    template < class base >
    class tbb_container
        extends public base
    {
        public:
            std::size_t size ( ) const;
            void        pop  ( );  
    };
    
} // namespace detail

#include "tbb_container.cpp"