#pragma once

using float16_t = typename std::conditional<sizeof(float)      ==16/8,float,
                  typename std::conditional<sizeof(double)     ==16/8,double,
                  typename std::conditional<sizeof(long double)==16/8,long double,
                                                                      std::float16_t
                                           >::type>::type>::type;

using float32_t = typename std::conditional<sizeof(float)      ==32/8,float,
                  typename std::conditional<sizeof(double)     ==32/8,double,
                  typename std::conditional<sizeof(long double)==32/8,long double,
                                                                      std::float32_t
                                           >::type>::type>::type;

using float64_t = typename std::conditional<sizeof(float)      ==64/8,float,
                  typename std::conditional<sizeof(double)     ==64/8,double,
                  typename std::conditional<sizeof(long double)==64/8,long double,
                                                                      std::float64_t
                                           >::type>::type>::type;

using float128_t = typename std::conditional<sizeof(float)      ==128/8,float,
                   typename std::conditional<sizeof(double)     ==128/8,double,
                   typename std::conditional<sizeof(long double)==128/8,long double,
                                                                        std::float128_t
                                            >::type>::type>::type;

using bfloat16_t = std::bfloat16_t;