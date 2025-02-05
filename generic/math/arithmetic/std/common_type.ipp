#pragma once

#define left_type  decay<decltype(left )>
#define right_type decay<decltype(right)>

} // Out of namespace ap


// Angle [degree,radian]

template < ap::degree_type type1, ap::degree_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::degree<typename common_type<typename type1::value_type,typename type2::value_type>::type>;
};

template < ap::radian_type type1, ap::radian_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::radian<typename common_type<typename type1::value_type,typename type2::value_type>::type>;
};

template < ap::degree_type type1, ap::radian_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::radian<typename common_type<typename type1::value_type,typename type2::value_type>::type>;
};

template < ap::radian_type type1, ap::degree_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::radian<typename common_type<typename type1::value_type,typename type2::value_type>::type>;
};





// Complex

template < ap::complex_type type1, ap::complex_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::complex<typename common_type<typename type1::value_type,typename type2::value_type>::type>;
};

template < ap::complex_type type1, ap::number_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::complex<typename common_type<typename type1::value_type,type2>::type>;
};

template < ap::number_type type1, ap::complex_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::complex<typename common_type<type1,typename type2::value_type>::type>;
};




namespace ap { // Back into namespace ap

#undef left_type
#undef right_type