#pragma once

/// Class constexpr_index

// Case int

template < int num >
struct constexpr_index<num>
{
    constexpr static const int value = num;
};



// Case char...

template < char digit >
    requires ( digit >= '0' and digit <= '9' )
struct constexpr_index<digit>
    extends public constexpr_index<int(digit-'0')>
{

};

template < char digit, char... digits >
    requires ( digit >= '0' and digit <= '9' and sizeof...(digits) >= 1 )
struct constexpr_index<digit,digits...>
    extends public constexpr_index<int((digit-'0')*pow(10,sizeof...(digits)) + constexpr_index<digits...>::value)>
{

};


/// Global

template < int num1, int num2 > constexpr_index<num1+num2> operator + ( const constexpr_index<num1>&, const constexpr_index<num2>& ) { return {}; }
template < int num1, int num2 > constexpr_index<num1-num2> operator - ( const constexpr_index<num1>&, const constexpr_index<num2>& ) { return {}; }
template < int num1, int num2 > constexpr_index<num1*num2> operator * ( const constexpr_index<num1>&, const constexpr_index<num2>& ) { return {}; }