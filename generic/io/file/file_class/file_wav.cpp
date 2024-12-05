#pragma once

// Header (declaration)

struct file_wav::chunk_header
{
    uint32_t           id             = 0;                   // Chunk-id expressed in 4 chars. Might be "RIFF", "fmt ", "data", ...
    uint32_t           size           = 0;                   // Chunk-size which represents the readable bytes in this chunk.
};

struct file_wav::guid // Used if and only if file_wav::chunk_fmt_extension == 65534 (wave-format-extension) and always set to fffe0000-0000-0010-800000aa00389b71.
{
    uint32_t           id_1           = 0xfffe0000;
    uint16_t           id_2           = 0x00;
    uint16_t           id_3           = 0x10;
    uint8_t            id_4[8]        = {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71};

    friend bool operator == ( const guid&, const guid& ) = default;
};





struct file_wav::riff_chunk
{
    chunk_header       header         = {};
    uint32_t           wave_tag       = from_string("WAVE"); // Always set to "WAVE".
    vector<chunk_ptr>  data           = {};                  // Subchunks of riff-chunk.
};

struct file_wav::fmt_chunk
{
    chunk_header       header         = {};
    uint16_t           format         = 1;                   // Shows the audio format, where { 1: PCM, 3: IEEE-floating-point, 6: A-law, 7: miu-law, 65534: Wav-Format-Extension... }.
    uint16_t           channel        = 2;                   // Shows the audio channel. e.x. 1: single_channel (like historical before 1950s), 2: normal, 6: 5.1 Stereo...
    uint32_t           rate           = 44100;               // Shows the audio sample rate. Most audio samples are 44.1kHz, while hifi-audio samples might be 48.0kHz, 192.0kHz or even higher.
    uint32_t           byte_rate      = 176400;              // Always set to rate * block_align.  (Notice 176400 Bps == 1411kbps).
    uint16_t           block_align    = 4;                   // Always set to channel * depth / 8.
    uint16_t           depth          = 16;                  // Shows the audio depth. Most audio depth are 16bits, while hifi-audio depth might be 32bits or even higher.
};

struct file_wav::fmt_extension_chunk
{
    chunk_header       header         = {};
    uint16_t           format         = 65534;               // Wav-Format-Extension.
    uint16_t           channel        = 2;                   // Same as above.
    uint32_t           rate           = 44100;               // Same as above.
    uint32_t           byte_rate      = 176400;              // Same as above.
    uint16_t           block_align    = 4;                   // Same as above.
    uint16_t           depth          = 16;                  // Same as above.
    uint16_t           extension_size = 22;                  // Size of this extension block.
    uint16_t           valid_depth    = 16;                  // Valid depth of the audio, usually less than or equal to depth.
    uint32_t           channel_mask   = 0x04;                // Mask of channel position. e.x. 0x01 = left-beyond, 0x04 = center, 0x3f = 5.1 channel.
    guid               fmt_guid       = guid();              // GUID of wave-format-extension.

};

struct file_wav::data_chunk
{
    chunk_header       header         = {};
 // matrix<float>      data           = {};                  // Audio data. Stored in file_wav.
};

struct file_wav::meta_chunk
{
    chunk_header       header         = {};
    string             data           = "";                  // Value is expressed in string.
};

struct file_wav::list_chunk
{
    chunk_header       header         = {};
    uint32_t           info_tag       = from_string("INFO"); // Always set to "INFO".
    vector<meta_chunk> data           = {};                  // Subchunks of list-chunk.
};

struct file_wav::id3_chunk
{
    chunk_header       header         = {};
    vector<char>       data           = {};                  // Non-standardized.
};

struct file_wav::chunk
    extends public variant<riff_chunk,fmt_chunk,fmt_extension_chunk,data_chunk,list_chunk,meta_chunk,id3_chunk>
{
    using variant::variant;
    using variant::operator=;
};










/// Class file_wav

// Core

file_wav::file_wav ( const char* pth )
{
    open(pth);
}

file_wav::file_wav ( const path& pth )
{
    open(pth);
}

// Interface (override)

file_wav& file_wav::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);
    let stream = file_stream(path(self), file_stream::read_only(true));

    // Read data.
    let ck = chunk();
    read(stream, ck);

    return self;
}

file_wav& file_wav::save ( )
{
    // Save file.
    file_interface::save();
    let stream = file_stream(path(self), file_stream::write_only(true), file_stream::erase(true));

    // Write data.
    write(stream);

    return self;
}

// Interface

int& file_wav::rate ( )
{
    return audio_rate;
}

const int& file_wav::rate ( ) const
{
    return audio_rate;
}

int& file_wav::depth ( )
{
    return audio_depth;
}

const int& file_wav::depth ( ) const
{
    return audio_depth;
}

string& file_wav::title ( )
{
    return audio_title;
}

const string& file_wav::title ( ) const
{
    return audio_title;
}

string& file_wav::artist ( )
{
    return audio_artist;
}

const string& file_wav::artist ( ) const
{
    return audio_artist;
}

string& file_wav::album ( )
{
    return audio_album;
}

const string& file_wav::album ( ) const
{
    return audio_album;
}

string& file_wav::year ( )
{
    return audio_year;
}

const string& file_wav::year ( ) const
{
    return audio_year;
}

string& file_wav::track ( )
{
    return audio_track;
}

const string& file_wav::track ( ) const
{
    return audio_track;
}

string& file_wav::genre ( )
{
    return audio_genre;
}

const string& file_wav::genre ( ) const
{
    return audio_genre;
}

string& file_wav::comment ( )
{
    return audio_comment;
}

const string& file_wav::comment ( ) const
{
    return audio_comment;
}



// Auxiliary

void file_wav::read ( file_stream& stream, file_wav::chunk& ck )
{
    let head = chunk_header();
    read(stream, head);

    if ( head.id == from_string("RIFF") )
    {
        ck = riff_chunk { .header = head };
        read(stream, ck.value<riff_chunk>());
    }

    else if ( head.id == from_string("fmt ") and head.size == 16 )
    {
        ck = fmt_chunk { .header = head };
        read(stream, ck.value<fmt_chunk>());
    }

    else if ( head.id == from_string("fmt ") and head.size == 40 )
    {
        ck = fmt_extension_chunk { .header = head };
        read(stream, ck.value<fmt_extension_chunk>());
    }

    else if ( head.id == from_string("data") )
    {
        ck = data_chunk { .header = head };
        read(stream, ck.value<data_chunk>());
    }

    else if ( head.id == from_string("LIST") )
    {
        ck = list_chunk { .header = head };
        read(stream, ck.value<list_chunk>());
    }

    else if ( head.id == from_string("ID3 ") or head.id == from_string("id3 ") )
    {
        ck = id3_chunk { .header = head };
        read(stream, ck.value<id3_chunk>() );
    }

    // Meta-chunk should never join polymoraphic reading, as it can only appear in list-chunk.

    else
        throw file_error("cannot open wav-file {}: chunk_header.id mismatches (with read = {:#x}, expected = {:#x}({}), {:#x}({}), {:#x}({}), {:#x}({}))", path(self), head.id, from_string("RIFF"), "RIFF", from_string("fmt "), "fmt ", from_string("data"), "data", from_string("LIST"), "LIST");
}

void file_wav::read ( file_stream& stream, file_wav::riff_chunk& ck )
{
    // Assume header has already been read.
    // Read body.
    ranges::binary_istream_view<file_stream,uint32_t,std::endian::little>(stream) >> ck.wave_tag;
    if ( ck.wave_tag != from_string("WAVE") )
        throw file_error("cannot open wav-file {}: riff_chunk.wave_tag mismatches (with read = {:#x}, expected = {:#x}({}))", path(self), ck.wave_tag, from_string("WAVE"), "WAVE");

    // Read data.
    int readable_bytes = ck.header.size - 4; // 4 = sizeof(ck.wave_tag).
    while ( readable_bytes >= 8 )
    {
        ck.data.push(std::make_unique<chunk>());
        read(stream, *ck.data[-1]);
        readable_bytes -= (8 + ck.data[-1]->visit([] (const auto& ck) { return ck.header.size; })); // 8 == sizeof(ck.header)

        if ( readable_bytes < 0 )
            throw file_error("cannot open wav-file {}: riff_chunk.header.size mismatches (with read = {}, expected = [[larger than read]])", path(self), ck.header.size);
    }
}

void file_wav::read ( file_stream& stream, file_wav::fmt_chunk& ck )
{
    // Assume header has already been read.
    // Read body.
    ranges::binary_istream_view<file_stream,uint16_t,std::endian::little>(stream) >> ck.format       >> ck.channel;
    ranges::binary_istream_view<file_stream,uint32_t,std::endian::little>(stream) >> ck.rate         >> ck.byte_rate;
    ranges::binary_istream_view<file_stream,uint16_t,std::endian::little>(stream) >> ck.block_align  >> ck.depth;
    if ( ck.format != 1 and ck.format != 3 and ck.format != 65534 )
        throw file_error("cannot open wav-file {}: fmt_chunk.format mismatches (with read = {:#x}, expected = {:#x}({}), {:#x}({}) {:#x}({})", path(self), ck.format, 1, "PCM", 3, "IEEE_Floating-Point", 65534, "Wav-Format-Extension");
    if ( ck.depth <= 0 or ck.depth % 8 != 0 )
        throw file_error("cannot open wav-file {}: fmt_chunk.depth mismatches (with read = {}, expected = 8, 16, 24, 32...)", path(self), ck.depth);
    if ( ck.format == 3 but ( ck.depth != 16 and ck.depth != 32 ) )
        throw file_error("cannot open wav-file {}: fmt_chunk.depth does not match any kind of floating-point required by fmt_chunk.format = [[3: IEEE-Floating-Point]] (with read = {}, expected = 16, 32)", path(self), ck.depth);

    // Set param.
    rate()        = ck.rate;
    depth()       = ck.depth;
    cache_format  = ck.format;
    cache_channel = ck.channel;
}

void file_wav::read ( file_stream& stream, file_wav::fmt_extension_chunk& ck )
{
    // Assume header has already been read.
    // Read body.
    ranges::binary_istream_view<file_stream,uint16_t,std::endian::little>(stream) >> ck.format           >> ck.channel;
    ranges::binary_istream_view<file_stream,uint32_t,std::endian::little>(stream) >> ck.rate             >> ck.byte_rate;
    ranges::binary_istream_view<file_stream,uint16_t,std::endian::little>(stream) >> ck.block_align      >> ck.depth;
    ranges::binary_istream_view<file_stream,uint16_t,std::endian::little>(stream) >> ck.extension_size   >> ck.valid_depth;
    ranges::binary_istream_view<file_stream,uint32_t,std::endian::little>(stream) >> ck.channel_mask;
    ranges::binary_istream_view<file_stream,uint32_t,std::endian::little>(stream) >> ck.fmt_guid.id_1;
    ranges::binary_istream_view<file_stream,uint16_t,std::endian::little>(stream) >> ck.fmt_guid.id_2    >> ck.fmt_guid.id_3;
    ranges::binary_istream_view<file_stream,uint8_t, std::endian::little>(stream) >> ck.fmt_guid.id_4[0] >> ck.fmt_guid.id_4[1]
                                                                                  >> ck.fmt_guid.id_4[2] >> ck.fmt_guid.id_4[3]
                                                                                  >> ck.fmt_guid.id_4[4] >> ck.fmt_guid.id_4[5]
                                                                                  >> ck.fmt_guid.id_4[6] >> ck.fmt_guid.id_4[7];
    if ( ck.format != 1 and ck.format != 3 and ck.format != 65534 )
        throw file_error("cannot open wav-file {}: fmt_extension_chunk.format mismatches (with read = {:#x}, expected = {:#x}({}), {:#x}({}), {:#x}({})", path(self), ck.format, 1, "PCM", 3, "IEEE-Floating-Point", 65534, "Wav-Format-Extension");
    if ( ck.depth <= 0 or ck.depth % 8 != 0 )
        throw file_error("cannot open wav-file {}: fmt_extension_chunk.depth mismatches (with read = {}, expected = 8, 16, 24, 32...)", path(self), ck.depth);
    if ( ck.format == 3 but ( ck.depth != 16 and ck.depth != 32 ) )
        throw file_error("cannot open wav-file {}: fmt_chunk.depth does not match any kind of floating-point required by fmt_chunk.format = [[3: IEEE-Floating-Point]] (with read = {}, expected = 16, 32)", path(self), ck.depth);

    // Set param.
    rate()        = ck.rate;
    depth()       = ck.depth;
    cache_format  = ck.format;
    cache_channel = ck.channel;
}

void file_wav::read ( file_stream& stream, file_wav::data_chunk& ck )
{
    // Assume header has already been read.
    // Read body (direct into file_wav).
    static_cast<vector<vector<float>>&>(self)
        = views::binary_istream<char,std::endian::little>(stream)
        | std::views::take(ck.header.size)
        | std::views::chunk(cache_channel * (depth() / 8))
        | std::views::transform([&] (auto&& frame)
            {
                return frame
                     | std::views::chunk(depth() / 8)
                     | std::views::transform([&] (auto&& val)
                         {
                             if ( ( cache_format == 1 or cache_format == 65534 ) and depth() == 8 ) // Stored as unsigned integer.
                             {
                                 uint8_t n = 0;
                                 uint8_t m = std::numeric_limits<uint8_t>::max();
                                 n = *val.begin();
                                 ++val.begin();
                                 return (float(n) / m) * 2 - 1; // [0,1] -> [-1,1]
                             }

                             else if ( ( cache_format == 1 or cache_format == 65534 ) and depth() >= 16 ) // Stored as signed integer.
                             {
                                 int64_t n = 0;
                                 int64_t m = std::numeric_limits<int64_t>::max();
                                 std::ranges::for_each(std::views::iota(0, depth()) | std::views::stride(8), [&] (int s)
                                     {
                                         n |= int64_t(uint8_t(*val.begin())) << (64 - depth() + s);
                                         ++val.begin();
                                     });
                                 return float(n) / m;
                             }

                             else if ( cache_format == 3 and depth() == 16 ) // Stored as IEEE float16_t.
                             {
                                 float16_t n = 0;
                                 std::ranges::copy(val, reinterpret_cast<char*>(&n));
                                 if constexpr ( aux::requires_byteswap<std::endian::little,int16_t> )
                                    aux::byteswap(n);
                                 return float(n);
                             }

                             else if ( cache_format == 3 and depth() == 32 ) // Stored as IEEE float32_t.
                             {
                                 float32_t n = 0;
                                 std::ranges::copy(val, reinterpret_cast<char*>(&n));
                                 if constexpr ( aux::requires_byteswap<std::endian::little,int16_t> )
                                    aux::byteswap(n);
                                 return float(n);
                             }

                             else
                                 throw file_error("cannot open wav-file {}: format or depth not supported (with format = {}, depth = {})", path(self), cache_format == 1 or cache_format == 65534 ? "[[integral]]" otherwise cache_format == 3 ? "[[floating-point]]" otherwise "[[bad-format]]", depth());
                         })
                     | std::ranges::to<vector<float>>(cache_channel);
            })
        | std::ranges::to<vector<vector<float>>>(ck.header.size / (cache_channel * (depth() / 8)));

    // Bug in std::views::take [[gcc]]
    // std::views::istream<char>(std::fstream) | std::views::take(n) will actually call n+1 std::fstream.read(char).

    /* Minimum reproducible case:
     *
     * auto stream  = std::ifstream("file.txt");        // Edit this file with content "abcd".
     * auto content = std::views::istream<char>(stream)
     *              | std::views::take(2)
     *              | std::ranges::to<std::string>();   // str == "ab".
     *
     * char ch;
     * stream >> ch;                                    // ch == 'd' (expected: 'c').
     */

    // Temporary fix way:
    // 1. explicitly call std::fstream.unget() to withdraw the last std::fstream.read(char).
    // 2. avoid using chunked_binary_istream_view.
    stream.unget();
}

void file_wav::read ( file_stream& stream, file_wav::list_chunk& ck )
{
    // Assume header has already been read.
    // Read body.
    ranges::binary_istream_view<file_stream,uint32_t,std::endian::little>(stream) >> ck.info_tag;
    if ( ck.info_tag != from_string("INFO") )
        throw file_error("cannot read wav-file {}: list_chunk.info_tag mismatches (with read = {:#x}, expected = {:#x}({}))", path(self), ck.info_tag, from_string("INFO"), "INFO");

    // Read data.
    int readable_bytes = ck.header.size - 4; // 4 = sizeof(ck.info_tag).
    while ( readable_bytes > 0 )
    {
        ck.data.push(meta_chunk());
        read(stream, ck.data[-1]);

        readable_bytes -= (8 + ck.data[-1].header.size); // 8 = sizeof(meta_chunk.header)
        if ( readable_bytes < 0 )
            throw file_error("cannot open wav-file {}: list_chunk.header.size mismatches (with read = {}, expected = [[larger than read]])", path(self), ck.header.size);
    }
}

void file_wav::read ( file_stream& stream, file_wav::meta_chunk& ck )
{
    // Assume header has not been read yet. Meta-chunk should never join polymoraphic reading, as it can only appear in list-chunk.
    // Read header.
    read(stream, ck.header);

    // Read body.
    ck.data.resize(ck.header.size);
    stream.read(ck.data.begin(), ck.header.size);
    if ( stream.peek() == '\0' ) // Sometimes a meta-chunk ends with 2 '\0'.
    {
        ck.header.size += 1;
        stream.get();
    }
    if ( ck.data.ends_with('\0') )
        ck.data.pop();

    // Set param.
    if ( ck.header.id == from_string("INAM") )
        title() = ck.data;
    else if ( ck.header.id == from_string("IART") )
        artist() = ck.data;
    else if ( ck.header.id == from_string("IPRD") )
        album() = ck.data;
    else if ( ck.header.id == from_string("ICRD") )
        year() = ck.data;
    else if ( ck.header.id == from_string("ITRK") )
        track() = ck.data;
    else if ( ck.header.id == from_string("IGNR") )
        genre() = ck.data;
    else if ( ck.header.id == from_string("ICMT") )
        comment() = ck.data;

    // Ignore other header id.
}

void file_wav::read ( file_stream& stream, file_wav::id3_chunk& ck )
{
    // Assume header has already been read.
    // Read body.
    ck.data = views::binary_istream<char,std::endian::little>(stream)
            | std::views::take(ck.header.size)
            | std::ranges::to<vector<char>>();

    // Bug in std::views::take [[gcc]]. See file_wav::read(file_stream&, file_wav::data_chunk&).
    stream.unget();
}

void file_wav::read ( file_stream& stream, file_wav::chunk_header& head )
{
    // Read header.
    ranges::binary_istream_view<file_stream,uint32_t,std::endian::little>(stream) >> head.id >> head.size;
}

void file_wav::write ( file_stream& stream )
{
    let riff_hd = chunk_header { .id           = from_string("RIFF"),
                                 .size         = uint32_t(4) /*default: data = empty*/ };
    let riff_ck = riff_chunk   { .header       = riff_hd,
                                 .wave_tag     = from_string("WAVE"),
                                 .data         = {} };

    let fmt_hd  = chunk_header { .id           = from_string("fmt "),
                                 .size         = uint32_t(16) };
    let fmt_ck  = fmt_chunk    { .header       = fmt_hd,
                                 .format       = uint16_t(1),
                                 .channel      = uint16_t(shape()[2]),
                                 .rate         = uint32_t(rate()),
                                 .byte_rate    = uint32_t(rate() * shape()[2] * (depth() / 8)),
                                 .block_align  = uint16_t(shape()[2] * (depth() / 8)),
                                 .depth        = uint16_t(depth()) };

    let data_hd = chunk_header { .id           = from_string("data"),
                                 .size         = uint32_t(size() * (depth() / 8)) };
    let data_ck = data_chunk   { .header       = data_hd };

    let list_hd = chunk_header { .id           = from_string("LIST"),
                                 .size         = uint32_t(4) /*default: data = empty*/ };
    let list_ck = list_chunk   { .header       = list_hd,
                                 .info_tag     = from_string("INFO"),
                                 .data         = {} };

    if ( title() != "" )
        list_ck.data.push ( meta_chunk { .header = chunk_header { .id = from_string("INAM"), .size = uint32_t(title().size()+1) /*value ends with '\0'*/ },
                                         .data   = title() } );
    if ( artist() != "" )
        list_ck.data.push ( meta_chunk { .header = chunk_header { .id = from_string("IART"), .size = uint32_t(artist().size()+1) /*value ends with '\0'*/ },
                                         .data   = artist() } );
    if ( album() != "" )
        list_ck.data.push ( meta_chunk { .header = chunk_header { .id = from_string("IPRD"), .size = uint32_t(album().size()+1) /*value ends with '\0'*/ },
                                         .data   = album() } );
    if ( year() != "" )
        list_ck.data.push ( meta_chunk { .header = chunk_header { .id = from_string("ICRD"), .size = uint32_t(year().size()+1) /*value ends with '\0'*/ },
                                         .data   = year() } );
    if ( track() != "" )
        list_ck.data.push ( meta_chunk { .header = chunk_header { .id = from_string("ITRK"), .size = uint32_t(track().size()+1) /*value ends with '\0'*/ },
                                         .data   = track() } );
    if ( genre() != "" )
        list_ck.data.push ( meta_chunk { .header = chunk_header { .id = from_string("IGNR"), .size = uint32_t(genre().size()+1) /*value ends with '\0'*/ },
                                         .data   = genre() } );
    if ( comment() != "" )
        list_ck.data.push ( meta_chunk { .header = chunk_header { .id = from_string("ICMT"), .size = uint32_t(comment().size()+1) /*value ends with '\0'*/ },
                                         .data   = comment() } );

    list_ck.header.size += list_ck.data.sum([] (const meta_chunk& ck) { return 8 + ck.header.size; });
    riff_ck.data         = { std::make_unique<chunk>(std::move(fmt_ck)), std::make_unique<chunk>(std::move(data_ck)), std::make_unique<chunk>(std::move(list_ck)) };
    riff_ck.header.size += riff_ck.data.sum([] (const chunk_ptr& ck_ptr) { return ck_ptr->visit([] (const auto& ck) { return 8 + ck.header.size; }); });

    write(stream, riff_ck);
}

void file_wav::write ( file_stream& stream, const chunk& ck )
{
    ck.visit([&] (const auto& c) { write(stream, c); });
}

void file_wav::write ( file_stream& stream, const riff_chunk& ck )
{
    write(stream, ck.header);
    ranges::binary_ostream_view<file_stream,uint32_t,std::endian::little>(stream) << ck.wave_tag;
    std::ranges::for_each(ck.data, [&] (const auto& ck_ptr) { write(stream, *ck_ptr); });
}

void file_wav::write ( file_stream& stream, const fmt_chunk& ck )
{
    if ( ck.depth <= 0 or ck.depth % 8 != 0 )
        throw file_error("cannot save wav-file {}: fmt_chunk.depth mismatches (with write = {}, expected = 8, 16, 24, 32...)", path(self), ck.depth);

    write(stream, ck.header);
    ranges::binary_ostream_view<file_stream,uint16_t,std::endian::little>(stream) << ck.format       << ck.channel;
    ranges::binary_ostream_view<file_stream,uint32_t,std::endian::little>(stream) << ck.rate         << ck.byte_rate;
    ranges::binary_ostream_view<file_stream,uint16_t,std::endian::little>(stream) << ck.block_align  << ck.depth;
}

void file_wav::write ( file_stream& stream, const fmt_extension_chunk& ck )
{
    if ( ck.depth <= 0 or ck.depth % 8 != 0 )
        throw file_error("cannot save wav-file {}: fmt_chunk.depth mismatches (with write = {}, expected = 8, 16, 24, 32...)", path(self), ck.depth);

    write(stream, ck.header);
    ranges::binary_ostream_view<file_stream,uint16_t,std::endian::little>(stream) << ck.format           << ck.channel;
    ranges::binary_ostream_view<file_stream,uint32_t,std::endian::little>(stream) << ck.rate             << ck.byte_rate;
    ranges::binary_ostream_view<file_stream,uint16_t,std::endian::little>(stream) << ck.block_align      << ck.depth;
    ranges::binary_ostream_view<file_stream,uint16_t,std::endian::little>(stream) << ck.extension_size   << ck.valid_depth;
    ranges::binary_ostream_view<file_stream,uint32_t,std::endian::little>(stream) << ck.channel_mask;
    ranges::binary_ostream_view<file_stream,uint32_t,std::endian::little>(stream) << ck.fmt_guid.id_1;
    ranges::binary_ostream_view<file_stream,uint16_t,std::endian::little>(stream) << ck.fmt_guid.id_2    << ck.fmt_guid.id_3;
    ranges::binary_ostream_view<file_stream,uint8_t, std::endian::little>(stream) << ck.fmt_guid.id_4[0] << ck.fmt_guid.id_4[1]
                                                                                  << ck.fmt_guid.id_4[2] << ck.fmt_guid.id_4[3]
                                                                                  << ck.fmt_guid.id_4[4] << ck.fmt_guid.id_4[5]
                                                                                  << ck.fmt_guid.id_4[6] << ck.fmt_guid.id_4[7];
}

void file_wav::write ( file_stream& stream, const data_chunk& ck )
{
    write(stream, ck.header);

    self | std::views::transform([&] (const auto& frame)
             {
                 return frame
                      | std::views::transform([&] (float val)
                          {
                              if ( val < -1.0 or val > 1.0 )
                                  throw file_error("cannot save wav-file {}: sound out of range (with write = {}, range = [-1.0,1.0])", path(self), val);


                              return std::views::iota(0, depth())
                                   | std::views::stride(8)
                                   | std::views::transform([&] (int s)
                                       {
                                           if ( depth() == 8 ) // Stored as unsigned integer.
                                           {
                                               let m = std::numeric_limits<uint8_t>::max();
                                               let n = uint8_t(round(((val + 1) / 2) * m));
                                               return char(n);
                                           }

                                           else // Stored as signed integer.
                                           {
                                               let m = std::numeric_limits<int64_t>::max();
                                               let n = int64_t(round(val * m));
                                               return char(uint8_t(n >> (64 - depth() + s)));
                                           }
                                       });
                          })
                      | std::views::join;
             })
         | std::views::join
         | std::ranges::to<views::binary_ostream<char,std::endian::little>>(std::ref(stream));
}

void file_wav::write ( file_stream& stream, const list_chunk& ck )
{
    write(stream, ck.header);
    ranges::binary_ostream_view<file_stream,uint32_t,std::endian::little>(stream) << ck.info_tag;
    std::ranges::for_each(ck.data, [&] (const meta_chunk& mtck) { write(stream, mtck); });
}

void file_wav::write ( file_stream& stream, const meta_chunk& ck )
{
    write(stream, ck.header);
    std::ranges::for_each(ck.data, [&] (char ch)
        {
            ranges::binary_ostream_view<file_stream,char,std::endian::little>(stream) << ch;
        });
    ranges::binary_ostream_view<file_stream,char,std::endian::little>(stream) << '\0';
}

void file_wav::write ( file_stream& stream, const id3_chunk& ck )
{
    write(stream, ck.header);
    std::ranges::for_each(ck.data, [&] (char ch)
        {
            ranges::binary_ostream_view<file_stream,char,std::endian::little>(stream) << ch;
        });
}

void file_wav::write ( file_stream& stream, const chunk_header& head )
{
    ranges::binary_ostream_view<file_stream,uint32_t,std::endian::little>(stream) << head.id << head.size;
}










constexpr uint32_t file_wav::from_string ( const string& str )
{
    let val = uint32_t(0);
    val |= uint32_t(uint8_t(str[1]));
    val |= uint32_t(uint8_t(str[2])) << 8;
    val |= uint32_t(uint8_t(str[3])) << 16;
    val |= uint32_t(uint8_t(str[4])) << 24;
    return val;
}

constexpr string file_wav::to_string ( const uint32_t& val )
{
    let str = string(4, '\0');
    str[1] = char(uint8_t(val    ));
    str[2] = char(uint8_t(val>>8 ));
    str[3] = char(uint8_t(val>>16));
    str[4] = char(uint8_t(val>>24));
    return str;
}





