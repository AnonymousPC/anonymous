#pragma once

#define left_type  decay<decltype(left )>
#define right_type decay<decltype(right)>



} // Out of namespace ap



// Class std::common_type

// Fraction

template < ap::fraction_type type1, ap::fraction_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::fraction<typename common_type<typename type1::value_type,typename type2::value_type>::type>;
};

template < ap::fraction_type type1, ap::int_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::fraction<typename common_type<typename type1::value_type,type2>::type>;
};

template < ap::fraction_type type1, ap::float_type type2 >
    requires ( not ap::fraction_type<type2> )
struct std::common_type<type1,type2>
{
    using type = type2;
};

template < ap::int_type type1, ap::fraction_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::fraction<typename common_type<type1,typename type2::value_type>::type>;
};

template < ap::float_type type1, ap::fraction_type type2 >
    requires ( not ap::fraction_type<type1> )
struct std::common_type<type1,type2>
{
    using type = type1;
};




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




// Polar

template < ap::polar_type type1, ap::polar_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::polar<typename common_type<typename type1::value_type,typename type2::value_type>::type,
                           typename common_type<typename type1::angle_type,typename type2::angle_type>::type
                          >;
};

template < ap::polar_type type1, ap::number_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::polar<typename common_type<typename type1::value_type,type2>::type,
                           typename                      type1::angle_type       ::type
                          >;
};

template < ap::number_type type1, ap::polar_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::polar<typename common_type<type1,typename type2::value_type>::type,
                           typename                            type2::angle_type ::type
                          >;
};






namespace ap // Back to namespace ap
{




#undef left_type
#undef right_type