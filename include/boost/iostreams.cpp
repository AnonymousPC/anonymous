module;
#undef in
#undef self
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/lzma.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filter/zstd.hpp>
#include <git/boost/libs/iostreams/src/bzip2.cpp>
#include <git/boost/libs/iostreams/src/file_descriptor.cpp>
#include <git/boost/libs/iostreams/src/gzip.cpp>
#include <git/boost/libs/iostreams/src/lzma.cpp>
#include <git/boost/libs/iostreams/src/mapped_file.cpp>
#include <git/boost/libs/iostreams/src/zlib.cpp>
#include <git/boost/libs/iostreams/src/zstd.cpp>

export module boost.iostreams;
export namespace boost::iostreams
{
    
}