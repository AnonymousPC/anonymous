#define left_type                 remove_cvref<decltype(left )>
#define left_key_type    typename remove_cvref<decltype(left )>::key_type
#define left_value_type  typename remove_cvref<decltype(left )>::value_type
#define right_type                remove_cvref<decltype(right)>
#define right_key_type   typename remove_cvref<decltype(right)>::key_type
#define right_value_type typename remove_cvref<decltype(right)>::value_type
#define cvt_type                  remove_cvref<decltype(cvt  )>
#define cvt_key_type     typename remove_cvref<decltype(cvt  )>::key_type
#define cvt_value_type   typename remove_cvref<decltype(cvt  )>::value_type