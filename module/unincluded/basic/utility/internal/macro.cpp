#define left_value_type      typename remove_cvref<decltype(left  )>::value_type
#define left_layout_type     typename remove_cvref<decltype(left  )>::layout_type
#define left_accessor_type   typename remove_cvref<decltype(left  )>::accessor_type
#define right_value_type     typename remove_cvref<decltype(right )>::value_type
#define right_layout_type    typename remove_cvref<decltype(right )>::layout_type
#define right_accessor_type  typename remove_cvref<decltype(right )>::accessor_type
#define output_value_type    typename remove_cvref<decltype(output)>::value_type
#define output_layout_type   typename remove_cvref<decltype(output)>::layout_type
#define output_accessor_type typename remove_cvref<decltype(output)>::accessor_type
#define vector_value_type    typename remove_cvref<decltype(vector)>::value_type
#define vector_layout_type   typename remove_cvref<decltype(vector)>::layout_type
#define mdspan_value_type    typename remove_cvref<decltype(mdspan)>::value_type
#define mdspan_element_type  typename remove_cvref<decltype(mdspan)>::element_type
#define mdspan_layout_type   typename remove_cvref<decltype(mdspan)>::layout_type
#define mdspan_accessor_type typename remove_cvref<decltype(mdspan)>::accessor_type
