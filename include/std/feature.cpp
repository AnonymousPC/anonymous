export module std.feature;

#ifndef __cpp_lib_aligned_accessor
    export import std.feature.aligned_accessor;
#endif

#ifndef __cpp_lib_hive
    export import std.feature.hive;
#endif

#ifndef __cpp_lib_inplace_vector
    export import std.feature.inplace_vector;
#endif

#ifndef __cpp_lib_is_layout_compatible
    export import std.feature.is_layout_compatible;
#endif

#ifndef __cpp_lib_mdspan
    export import std.feature.mdspan;
#endif

#ifndef __cpp_lib_range_as_const
    export import std.feature.ranges.as_const;
#endif

#ifndef __cpp_lib_ranges_chunk
    export import std.feature.ranges.chunk;
#endif

#ifndef __cpp_lib_ranges_join_with
    export import std.feature.ranges.join_with;
#endif

#ifndef __cpp_lib_ranges_starts_ends_with
    export import std.feature.ranges.starts_ends_with;
#endif

#ifndef __cpp_lib_ranges_stride
    export import std.feature.ranges.stride;
#endif

#ifndef __cpp_lib_ranges_zip
    export import std.feature.ranges.zip;
#endif

#ifndef __cpp_lib_sender
    export import std.feature.sender;
#endif

#ifndef __cpp_lib_stacktrace
    export import std.feature.stacktrace;
#endif

#ifndef __cpp_lib_submdpsan
    export import std.feature.submdspan;
#endif

#ifndef __cpp_lib_text_encoding
    export import std.feature.text_encoding;
#endif
