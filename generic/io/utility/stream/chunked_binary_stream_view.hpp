#pragma once

namespace ranges
{

template < class stream_type, class input_type, std::endian endian = std::endian::native >
class chunked_binary_istream_view
    extends public std::ranges::view_interface<chunked_binary_istream_view<stream_type,input_type>>
{
    private: // Precondition
        static_assert ( requires ( stream_type s, input_type t ) { s.read(reinterpret_cast<char*>(&t), sizeof(input_type)); } );
        static_assert ( not is_class<input_type> );

    private: // Data
        stream_type*       s_ptr = nullptr;
        vector<input_type> t     = {};

    private: // Typedef
        class iterator;

    public: // Interface
        constexpr chunked_binary_istream_view ( stream_type&, int );
        constexpr auto begin ( );
        constexpr auto end   ( );
};






template < class stream_type, class output_type, std::endian endian = std::endian::native >
class chunked_binary_ostream_view
{
    private: // Precondition
        static_assert ( requires ( stream_type s, output_type t ) { s.write(reinterpret_cast<const char*>(&t), sizeof(output_type)); } );
        static_assert ( not is_class<output_type> );

    public: // Interface
        constexpr chunked_binary_ostream_view ( std::from_range_t, input_range auto&& r, stream_type&, int )
            requires same_as<output_type,decay<decltype(*(*r.begin()).begin())>>;
};


} // namespace ranges





namespace views
{

template < class input_type, std::endian endian = std::endian::native >
constexpr auto chunked_binary_istream ( auto& /*stream_type*/ s, int )
    requires requires ( input_type t ) { s.read(reinterpret_cast<char*>(&t), sizeof(input_type)); };

template < class output_type, std::endian endian = std::endian::native >
class chunked_binary_ostream
{
    public:
        constexpr chunked_binary_ostream ( std::from_range_t, input_range auto&& r, auto /*std::reference_wrapper<stream_type>*/ s, int chunk_len )
            requires requires ( output_type t ) { s.get().write(reinterpret_cast<const char*>(&t), sizeof(output_type)); };
};

} // namespace views




#include "chunked_binary_stream_view.ipp"