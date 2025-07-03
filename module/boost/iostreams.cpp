module;
#undef in
#undef self
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/lzma.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filter/zstd.hpp>
#include <boost/iostreams/src/bzip2.cpp>
#include <boost/iostreams/src/file_descriptor.cpp>
#include <boost/iostreams/src/gzip.cpp>
#include <boost/iostreams/src/lzma.cpp>
#include <boost/iostreams/src/mapped_file.cpp>
#include <boost/iostreams/src/zlib.cpp>
#include <boost/iostreams/src/zstd.cpp>

export module boost.iostreams;
import std;
import bzip2;
import xz;
import zlib;
import zstd;

export namespace boost::iostreams
{
    
}