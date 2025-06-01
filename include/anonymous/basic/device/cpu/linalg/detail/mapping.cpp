namespace detail
{
    enum { eigen_map_default,
           eigen_map_vector,
           eigen_map_matrix,
           eigen_map_tensor };

    constexpr auto eigen_make_extents ( auto extents )
    {
        auto arr = std::array<int,extents.rank()>();
        for_constexpr<0,extents.rank()-1>([&] <int index> { arr[index] = extents.extent(index); });
        return arr;
    }

    constexpr auto eigen_make_strided_full_extents ( auto extents, auto mapping )
    {
        auto arr = std::array<int,extents.rank()+1>();
        for_constexpr<0,extents.rank()-1>([&] <int index> { arr[index] = extents.extent(index); });
        arr[extents.rank()] = mapping.stride(0);
        return arr;
    }

    template < int rank >
    constexpr auto eigen_make_transpose_shuffle ( )
    {
        auto arr = std::array<int,rank>();
        for_cons
    }

    template < auto mode = eigen_map_default >
    constexpr auto eigen_map_helper ( auto mdspan )
    {
        if constexpr ( ( mode == eigen_map_default and mdspan.rank() == 1 ) or mode == eigen_map_vector )
            if constexpr ( same_as<mdspan_layout_type,std::layout_right> or same_as<mdspan_layout_type,std::layout_left> )
                if constexpr ( not is_const<mdspan_element_type> )
                    return Eigen::Map<      Eigen::Vector<mdspan_value_type,Eigen::Dynamic>>(mdspan.data_handle(), mdspan.size());
                else  
                    return Eigen::Map<const Eigen::Vector<mdspan_value_type,Eigen::Dynamic>>(mdspan.data_handle(), mdspan.size());
            else if constexpr ( same_as<mdspan_layout_type,std::layout_stride> )
                if constexpr ( not is_const<mdspan_element_type> )
                    return Eigen::Map<      Eigen::Vector<mdspan_value_type,Eigen::Dynamic>,Eigen::Unaligned,Eigen::InnerStride<Eigen::Dynamic>>(mdspan.data_handle(), mdspan.size(), mdspan.stride(0));
                else
                    return Eigen::Map<const Eigen::Vector<mdspan_value_type,Eigen::Dynamic>,Eigen::Unaligned,Eigen::InnerStride<Eigen::Dynamic>>(mdspan.data_handle(), mdspan.size(), mdspan.stride(0));

        else if constexpr ( ( mode == eigen_map_default and mdspan.rank() == 2 ) or mode == eigen_map_matrix )
            if constexpr ( same_as<mdspan_layout_type,std::layout_right> )
                if constexpr ( not is_const<mdspan_element_type> )
                    return Eigen::Map<      Eigen::Matrix<mdspan_value_type,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(mdspan.data_handle(), mdspan.extent(0), mdspan.extent(1));
                else 
                    return Eigen::Map<const Eigen::Matrix<mdspan_value_type,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(mdspan.data_handle(), mdspan.extent(0), mdspan.extent(1));
            else if constexpr ( same_as<mdspan_layout_type,std::layout_left> )
                if constexpr ( not is_const<mdspan_element_type> )
                    return Eigen::Map<      Eigen::Matrix<mdspan_value_type,Eigen::Dynamic,Eigen::Dynamic,Eigen::ColMajor>>(mdspan.data_handle(), mdspan.extent(1), mdspan.extent(0));
                else
                    return Eigen::Map<const Eigen::Matrix<mdspan_value_type,Eigen::Dynamic,Eigen::Dynamic,Eigen::ColMajor>>(mdspan.data_handle(), mdspan.extent(1), mdspan.extent(0));
            else if constexpr ( same_as<mdspan_layout_type,std::layout_stride> )
                if constexpr ( not is_const<mdspan_element_type> )
                    return Eigen::Map<      Eigen::Matrix<mdspan_value_type,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::Unaligned,Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>>(mdspan.data_handle(), mdspan.extent(0), mdspan.extent(1), Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(mdspan.stride(0), mdspan.stride(1)));
                else
                    return Eigen::Map<const Eigen::Matrix<mdspan_value_type,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::Unaligned,Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>>(mdspan.data_handle(), mdspan.extent(0), mdspan.extent(1), Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(mdspan.stride(0), mdspan.stride(1)));

        else if constexpr ( ( mode == eigen_map_default and mdspan.rank() >= 3 ) or mode == eigen_map_tensor )
            if constexpr ( same_as<mdspan_layout_type,std::layout_right> )
                if constexpr ( not is_const<mdspan_element_type> )   
                    return Eigen::TensorMap<      Eigen::Tensor<mdspan_value_type,mdspan.rank(),Eigen::RowMajor>>(mdspan.data_handle(), eigen_make_extents(mdspan.extents()));
                else
                    return Eigen::TensorMap<const Eigen::Tensor<mdspan_value_type,mdspan.rank(),Eigen::RowMajor>>(mdspan.data_handle(), eigen_make_extents(mdspan.extents()));
            else if constexpr ( same_as<mdspan_layout_type,std::layout_left> )
                if constexpr ( not is_const<mdspan_element_type> )
                    return Eigen::TensorMap<      Eigen::Tensor<mdspan_value_type,mdspan.rank(),Eigen::ColMajor>>(mdspan.data_handle(), eigen_make_extents(mdspan.extents());
                else 
                    return Eigen::TensorMap<const Eigen::Tensor<mdspan_value_type,mdspan.rank(),Eigen::ColMajor>>(mdspan.data_handle(), eigen_make_extents(mdspan.extents());
            else if constexpr ( same_as<mdspan_layout_type,std::layout_stride> )
                if constexpr ( not is_const<mdspan_element_type> )
                    return Eigen::TensorMap<      Eigen::Tensor<mdspan_value_type,mdspan.rank()+1,Eigen::RowMajor>>(mdspan.data_handle(), eigen_make_strided_full_extents(mdspan.extents(), mdspan.mapping())).template chip<mdspan.rank()>(0).shuffle(eigen_make_transpose_shuffle<mdspan.rank()>());
                else
                    return Eigen::TensorMap<const Eigen::Tensor<mdspan_value_type,mdspan.rank()+1,Eigen::RowMajor>>(mdspan.data_handle(), eigen_make_strided_full_extents(mdspan.extents(), mdspan.mapping())).template chip<mdspan.rank()>(0).shuffle(eigen_make_transpose_shuffle<mdspan.rank()>());
   
    }

    template < class type = void, auto mode = eigen_map_default >
    constexpr auto eigen_map ( auto mdspan )
    {
        if constexpr ( is_void<type> or same_as<type,mdspan_value_type> )
            return eigen_map_helper<mode>(mdspan);
        else
            return eigen_map_helper<mode>(mdspan).template cast<type>();
    }

} // namespace detail



/* Case: rank() >= 3, same_as<mdspan_layout_type,std::layout_strided>
 * Guarantee: mdspan is somehow a `column_view` of a host array.
 * Eigen::TensorMap does not provides Eigen::Stride template,
 * so that it's essential for us to manual map data into Eigen.
 * 
 * Consider a host array<int,5> (with shape = {2, 2, 3, 3, 4}):
 * {{{{{  0,   1,   2,   3},
 *     {  4,   5,   6,   7},
 *     {  8,   9,  10,  11}},
 *
 *    {{ 12,  13,  14,  15},
 *     { 16,  17,  18,  19},
 *     { 20,  21,  22,  23}},
 *
 *    {{ 24,  25,  26,  27},
 *     { 28,  29,  30,  31},
 *     { 32,  33,  34,  35}}},
 *
 *
 *   {{{ 36,  37,  38,  39},
 *     { 40,  41,  42,  43},
 *     { 44,  45,  46,  47}},
 *
 *    {{ 48,  49,  50,  51},
 *     { 52,  53,  54,  55},
 *     { 56,  57,  58,  59}},
 *
 *    {{ 60,  61,  62,  63},
 *     { 64,  65,  66,  67},
 *     { 68,  69,  70,  71}}}},
 *
 *
 *
 *  {{{{ 72,  73,  74,  75},
 *     { 76,  77,  78,  79},
 *     { 80,  81,  82,  83}},
 *
 *    {{ 84,  85,  86,  87},
 *     { 88,  89,  90,  91},
 *     { 92,  93,  94,  95}},
 *
 *    {{ 96,  97,  98,  99},
 *     {100, 101, 102, 103},
 *     {104, 105, 106, 107}}},
 *
 *
 *   {{{108, 109, 110, 111},
 *     {112, 113, 114, 115},
 *     {116, 117, 118, 119}},
 *
 *    {{120, 121, 122, 123},
 *     {124, 125, 126, 127},
 *     {128, 129, 130, 131}},
 *
 *    {{132, 133, 134, 135},
 *     {136, 137, 138, 139},
 *     {140, 141, 142, 143}}}}}
 * 
 * imagine the case we have a mdpsan = host.transpose()[1][1], that is
 * {{{  0,  72} 
 *   { 36, 108}} 
 * 
 *  {{ 12,  84}
 *   { 48, 120}}
 *  
 *  {{ 24,  96}
 *   { 60, 132}}}
 * with mdspan.extents() = {3, 2, 2}, mdspan.strides() = {12, 36, 72} = {3*4, 3*3*4, 2*3*3*4}
 * 
 * We wanna map the latter one into Eigen::TensorMap, we need to:
 * 1. Create a full Eigen::TensorMap with 
 *        data  = mdspan.data_handle(),                     e.g. [[mdspan.data()]]
 *        rank  = extents.rank() + 1,                       e.g. 4
 *        shape = {mdspan.extents()...T, mdspan.stride(0)}, e.g. {2, 2, 3, 12}
 * 2. chip<TensorMapLastDimension>(0).
 * 3. transpose.
 */