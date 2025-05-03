template < int dim >
class detail::array_shape
    extends public std::array<int,dim>
{
    public: // Core
        constexpr array_shape ( );
        constexpr array_shape ( int_type auto... args ) requires ( sizeof...(args) == dim );

    public: // Member
        constexpr static int  size        ( );
        constexpr        int& operator [] ( int );
        constexpr const  int& operator [] ( int ) const;
};