module;
#include <version>

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

export import std.feature.ranges;

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
