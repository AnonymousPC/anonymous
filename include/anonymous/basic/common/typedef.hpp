using nullptr_t = std::nullptr_t;
using ptrdiff_t = std::ptrdiff_t;
using size_t    = std::size_t;

using int8_t         = std::int8_t;
using int16_t        = std::int16_t;
using int32_t        = std::int32_t;
using int64_t        = std::int64_t;
using int_fast8_t    = std::int_fast8_t;
using int_fast16_t   = std::int_fast16_t;
using int_fast32_t   = std::int_fast32_t;
using int_fast64_t   = std::int_fast64_t;
using int_least8_t   = std::int_least8_t;
using int_least16_t  = std::int_least16_t;
using int_least32_t  = std::int_least32_t;
using int_least64_t  = std::int_least64_t;
using intmax_t       = std::intmax_t;

using uint8_t        = std::uint8_t;
using uint16_t       = std::uint16_t;
using uint32_t       = std::uint32_t;
using uint64_t       = std::uint64_t;
using uint_fast8_t   = std::uint_fast8_t;
using uint_fast16_t  = std::uint_fast16_t;
using uint_fast32_t  = std::uint_fast32_t;
using uint_fast64_t  = std::uint_fast64_t;
using uint_least8_t  = std::uint_least8_t;
using uint_least16_t = std::uint_least16_t;
using uint_least32_t = std::uint_least32_t;
using uint_least64_t = std::uint_least64_t;
using uintmax_t      = std::uintmax_t;

using float16_t = conditional<sizeof(float)      ==16/8,float,
                  conditional<sizeof(double)     ==16/8,double,
                  conditional<sizeof(long double)==16/8,long double,
                                                        #ifdef __STDCPP_FLOAT16_T__
                                                        std::float16_t
                                                        #else
                                                        void
                                                        #endif
                             >>>;

using float32_t = conditional<sizeof(float)      ==32/8,float,
                  conditional<sizeof(double)     ==32/8,double,
                  conditional<sizeof(long double)==32/8,long double,
                                                        #ifdef __STDCPP_FLOAT32_T__
                                                        std::float32_t
                                                        #else
                                                        void
                                                        #endif
                             >>>;

using float64_t = conditional<sizeof(float)      ==64/8,float,
                  conditional<sizeof(double)     ==64/8,double,
                  conditional<sizeof(long double)==64/8,long double,
                                                        #ifdef __STDCPP_FLOAT64_T__
                                                        std::float64_t
                                                        #else
                                                        void
                                                        #endif
                             >>>;

using float128_t = conditional<sizeof(float)      ==128/8,float,
                   conditional<sizeof(double)     ==128/8,double,
                   conditional<sizeof(long double)==128/8,long double,
                                                          #ifdef __STDCPP_FLOAT128_T__
                                                          std::float128_t
                                                          #else
                                                          void
                                                          #endif
                              >>>;