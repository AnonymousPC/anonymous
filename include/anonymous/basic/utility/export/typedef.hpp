using float16_t = std::conditional_t<sizeof(float)      ==16/8,float,
                  std::conditional_t<sizeof(double)     ==16/8,double,
                  std::conditional_t<sizeof(long double)==16/8,long double,
                                                               #ifdef __STDCPP_FLOAT16_T__
                                                               std::float16_t
                                                               #else
                                                               void
                                                               #endif
                                    >>>;

using float32_t = std::conditional_t<sizeof(float)      ==32/8,float,
                  std::conditional_t<sizeof(double)     ==32/8,double,
                  std::conditional_t<sizeof(long double)==32/8,long double,
                                                               #ifdef __STDCPP_FLOAT32_T__
                                                               std::float32_t
                                                               #else
                                                               void
                                                               #endif
                                    >>>;

using float64_t = std::conditional_t<sizeof(float)      ==64/8,float,
                  std::conditional_t<sizeof(double)     ==64/8,double,
                  std::conditional_t<sizeof(long double)==64/8,long double,
                                                               #ifdef __STDCPP_FLOAT64_T__
                                                               std::float64_t
                                                               #else
                                                               void
                                                               #endif
                                    >>>;

using float128_t = std::conditional_t<sizeof(float)      ==128/8,float,
                   std::conditional_t<sizeof(double)     ==128/8,double,
                   std::conditional_t<sizeof(long double)==128/8,long double,
                                                                 #ifdef __STDCPP_FLOAT128_T__
                                                                 std::float128_t
                                                                 #else
                                                                 void
                                                                 #endif
                                    >>>;