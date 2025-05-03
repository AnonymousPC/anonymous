#define left_type                  remove_cvref<decltype(left )>
#define left_key_type     typename remove_cvref<decltype(left )>::key_type
#define left_value_type   typename remove_cvref<decltype(left )>::value_type
#define left_device_type  typename remove_cvref<decltype(left )>::device_type
#define right_type                 remove_cvref<decltype(right)>
#define right_key_type    typename remove_cvref<decltype(right)>::key_type
#define right_value_type  typename remove_cvref<decltype(right)>::value_type
#define right_device_type typename remove_cvref<decltype(right)>::device_type