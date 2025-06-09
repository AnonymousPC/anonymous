module;
#undef in
#undef self
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/lzma.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filter/zstd.hpp>
#include <boost/iostreams/bzip2.cpp>
#include <boost/iostreams/file_descriptor.cpp>
#include <boost/iostreams/gzip.cpp>
#include <boost/iostreams/lzma.cpp>
#include <boost/iostreams/mapped_file.cpp>
#include <boost/iostreams/zlib.cpp>
#include <boost/iostreams/zstd.cpp>

export module boost.iostreams;
import std;

export namespace boost::iostreams
{
    
}