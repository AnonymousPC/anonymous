#pragma once

namespace ranges
{

template < class stream_type, class input_type >
class istream_view
    extends public std::ranges::view_interface<istream_view<stream_type,input_type>>
{
    private: // Precondition
        static_assert ( requires ( stream_type s, input_type t ) { s >> t; } );

    private: // Data
        stream_type* s_ptr = nullptr;
        input_type   t     = input_type();

    private: // Typedef
        class iterator;

    public: // Interface
        constexpr istream_view ( stream_type& );
        constexpr auto begin ( );
        constexpr auto end   ( );
};






template < class stream_type, class output_type >
class ostream_view
{
    private: // Precondition
        static_assert ( requires ( stream_type s, output_type t ) { s << t; } );

    public: // Interface
        constexpr ostream_view ( std::from_range_t, std::ranges::input_range auto&& r, stream_type& )
            requires std::same_as<output_type,decay<decltype(*r.begin())>>;
};


} // namespace ranges





namespace views
{

template < class input_type >
constexpr auto istream ( auto& s )
    requires requires ( input_type t ) { s >> t; };

template < class output_type >
class ostream
{
    public:
        constexpr ostream ( std::from_range_t, std::ranges::input_range auto&& r, auto /*std::reference_wrapper<stream_type>*/ s )
            requires requires ( output_type t ) { s.get() << t; };
};

} // namespace views




#include "stream_view.ipp"