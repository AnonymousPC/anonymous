#pragma once

using float16_t = typename std::conditional<sizeof(float)      ==16/8,float,
                  typename std::conditional<sizeof(double)     ==16/8,double,
                  typename std::conditional<sizeof(long double)==16/8,long double,
                                                                      #if __STDCPP_FLOAT16_T__
                                                                      ::float16_t
                                                                      #else
                                                                      void
                                                                      #endif
                                           >::type>::type>::type;

using float32_t = typename std::conditional<sizeof(float)      ==32/8,float,
                  typename std::conditional<sizeof(double)     ==32/8,double,
                  typename std::conditional<sizeof(long double)==32/8,long double,
                                                                      #if __STDCPP_FLOAT32_T__
                                                                      ::float32_t
                                                                      #else
                                                                      void
                                                                      #endif
                                           >::type>::type>::type;

using float64_t = typename std::conditional<sizeof(float)      ==64/8,float,
                  typename std::conditional<sizeof(double)     ==64/8,double,
                  typename std::conditional<sizeof(long double)==64/8,long double,
                                                                      #if __STDCPP_FLOAT64_T__
                                                                      ::float64_t
                                                                      #else
                                                                      void
                                                                      #endif
                                           >::type>::type>::type;

using float128_t = typename std::conditional<sizeof(float)      ==128/8,float,
                   typename std::conditional<sizeof(double)     ==128/8,double,
                   typename std::conditional<sizeof(long double)==128/8,long double,
                                                                        #if __STDCPP_FLOAT128_T__ and not defined(_LIBCPP_STD_VER)
                                                                        ::float128_t
                                                                        #else
                                                                        void
                                                                        #endif
                                            >::type>::type>::type;

using bfloat16_t = 
    #if __STDCPP_BFLOAT16_T__
    ::bfloat16_t
    #else
    void
    #endif
    ;