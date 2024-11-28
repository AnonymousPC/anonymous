#pragma once

namespace ranges
{

template < class stream_type, class input_type, std::endian endian = std::endian::native >
class binary_istream_view
    extends public std::ranges::view_interface<binary_istream_view<stream_type,input_type,endian>>
{
    private: // Precondition
        static_assert ( requires ( stream_type s, input_type t ) { s.read(reinterpret_cast<char*>(&t), sizeof(input_type)); } );
        static_assert ( not is_class<input_type> );

    private: // Data
        stream_type* s_ptr = nullptr;
        input_type   t     = input_type();

    private: // Typedef
        class iterator;

    public: // Interface
        constexpr binary_istream_view ( stream_type& );
        constexpr auto begin ( );
        constexpr auto end   ( );

    public: // As-stream
        constexpr binary_istream_view& operator >> ( std::same_as<input_type> auto& );
};






template < class stream_type, class output_type, std::endian endian = std::endian::native >
class binary_ostream_view
{
    private: // Precondition
        static_assert ( requires ( stream_type s, output_type t ) { s.write(reinterpret_cast<const char*>(&t), sizeof(output_type)); } );
        static_assert ( not is_class<output_type> );

    public: // Interface
        constexpr binary_ostream_view ( std::from_range_t, std::ranges::input_range auto&& r, stream_type& )
            requires std::same_as<output_type,decay<decltype(*r.begin())>>;

    public: // As-stream
        constexpr binary_ostream_view& operator << ( const std::same_as<output_type> auto& );

    public: // As-stream-aux
        constexpr binary_ostream_view ( stream_type& );

    private: // As-stream-aux
        stream_type* s_ptr = nullptr; // Only in as-stream mode it will point to real stream.
};


} // namespace ranges





namespace views
{

template < class input_type, std::endian endian = std::endian::native >
constexpr auto binary_istream ( auto& /*stream_type*/ s )
    requires requires ( input_type t ) { s.read(reinterpret_cast<char*>(&t), sizeof(input_type)); };

template < class output_type, std::endian endian = std::endian::native >
class binary_ostream
{
    public:
        constexpr binary_ostream ( std::from_range_t, std::ranges::input_range auto&& r, auto /*std::reference_wrapper<stream_type>*/ s )
            requires requires ( output_type t ) { s.get().write(reinterpret_cast<const char*>(&t), sizeof(output_type)); };
};

} // namespace views




#include "binary_stream_view.ipp"