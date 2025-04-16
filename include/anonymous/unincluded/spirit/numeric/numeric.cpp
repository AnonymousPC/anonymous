#pragma once

/// Auxiliary

template < string_type type1, class type2 >
class aux::symbol_map
    extends public map<type1,type2>
{
    public: // Interface
        type2* find ( const char*& ptr_begin, const char* ptr_end, auto )
        {
            for ( auto ptr in range ( ptr_end, ptr_begin + 1, -1 ) )
                if ( self.keys().contains(string_view(ptr_begin, ptr)) )
                {
                    auto& v = self[string_view(ptr_begin, ptr)];
                    ptr_begin = ptr;
                    return &v;
                }
            return nullptr;
        }

        const type2* find ( const char*& ptr_begin, const char* ptr_end, auto ) const
        {
            for ( auto ptr in range ( ptr_end, ptr_begin + 1, -1 ) )
                if ( self.keys().contains(string_view(ptr_begin, ptr)) )
                {
                    const auto& v = self[string_view(ptr_begin, ptr)];
                    ptr_begin = ptr;
                    return &v;
                }
            return nullptr;
        }
};




template < std::integral input_type >
struct aux::boost_spirit_number_rule_helper<input_type>
{
    using type = boost::spirit::qi::uint_parser<input_type>;
};

template < std::floating_point input_type >
struct aux::boost_spirit_number_rule_helper<input_type>
{
    using type = boost::spirit::qi::real_parser<input_type,boost::spirit::qi::ureal_policies<input_type>>;
};




/// Class numeric_expr<type>

template < class type >
numeric_expr<type>::numeric_expr ( )
    extends expression ( token_1 )
{
    using namespace boost::spirit::qi;
    using namespace boost::phoenix;

    token_1 =   ( (        token_2 ) [_val =  _1]
                | ( '+' >> token_2 ) [_val = +_1]
                | ( '-' >> token_2 ) [_val = -_1] )
            >> *( ( '+' >> token_2 ) [_val += _1]
                | ( '-' >> token_2 ) [_val -= _1] );

    token_2 = token_3 | token_4;

    token_3 =   (          token_4 ) [_val =  _1]
            >> *( ( '*' >> token_4 ) [_val *= _1]
                | ( '/' >> token_4 ) [_val /= _1] );

    token_4 = ( ( token_5   >> token_6_p ) [_val = bind(binary_multiply, _1, _2)]
              | ( token_5_p |  token_6_p ) [_val = _1                           ] );

    token_5 = type_ [_val = _1];

    token_5_p =   (          token_5             ) [_val = _1                        ]
              >> -( '^' >> ( token_5 | token_6 ) ) [_val = bind(binary_pow, _val, _1)];

    token_6 = ( ( '(' >> expression  >> ')'                                           ) [_val = _1            ]
              | (        token_fun_0 >> '(' >> ')'                                    ) [_val = bind(_1)      ]
              | (        token_fun_1 >> '(' >> expression >> ')'                      ) [_val = bind(_1,_2)   ]
              | (        token_fun_2 >> '(' >> expression >> ',' >> expression >> ')' ) [_val = bind(_1,_2,_3)]
              | (        token_con                                                    ) [_val = _1            ] );

    token_6_p =   (                    token_6   ) [_val = _1                        ]
              >> -( '^' >> ( token_5 | token_6 ) ) [_val = bind(binary_pow, _val, _1)];
}

//template < class type >
//numeric_expr<type>::numeric_expr ( )
//    extends expression ( add_minus )
//{
//    using namespace boost::spirit::qi;
//    using namespace boost::phoenix;
//
//    // The whole expression contains one or several addable/minusable parts.                  e.x. x + y + z.
//    // Besides, the prefix '+'/'-' only affects the first part.                               e.x. - x + y.
//    add_minus =   ( (        term ) [_val =  _1]
//                  | ( '+' >> term ) [_val = +_1]
//                  | ( '-' >> term ) [_val = -_1] )
//              >> *( ( '+' >> term ) [_val += _1]
//                  | ( '-' >> term ) [_val -= _1] );
//
//    // A term is addable/minusable with one another, iff one of the following is true:
//    // 1. It contains one or several multipliable/dividable parts.                            e.x. x * y * z.
//    // 2. It is a powered expression.                                                         e.x. 2x^2.
//    // Notice a raw/unparenthesised powered expression is not multipliable.                   e.x. 2x^2 * 3x^3 (ambiguous: 2x^2*3x^3).
//    term    = mul_div
//            | powered;
//
//    // A multiply or divide result contains one or several multipliable/dividable parts.      e.x. x * y * z.
//    mul_div =   (          factor ) [_val =  _1]
//            >> *( ( '*' >> factor ) [_val *= _1]
//                | ( '/' >> factor ) [_val /= _1] );
//
//    // A powered expression contains none or several headers and one powered term at the end. e.x. (x+1)(x+2)x^3.
//    // '*' is between them.
//
//    powered =
//
//
//    factor     = ( )
//
//    token_2 = token_3 | token_4;
//
//    token_3 =   (          token_4 ) [_val =  _1]
//            >> *( ( '*' >> token_4 ) [_val *= _1]
//                | ( '/' >> token_4 ) [_val /= _1] );
//
//    token_4 = type_or_con_or_paren >> con_or_paren_p // 2(x+1)^2, 2x^2, (x+1)(x-1)^2, 2(x-1)^2
//            | type_or_con_or_paren_p                 // 2^2, x^2, (2x)^;
//
//    token_xxx_p = token_xxx >> '^' >> type_or_con_or_paren; // 2(x+1)^(x+1);
//
//    token_func = token_fun_0 >> ...;
//
//
//
//    token_4 = ( ( token_5   >> token_6_p ) [_val = bind(binary_multiply, _1, _2)]
//              | ( token_5_p |  token_6_p ) [_val = _1                           ] );
//
//    token_5 = type_ [_val = _1];
//
//    token_5_p =   (          token_5             ) [_val = _1                        ]
//              >> -( '^' >> ( token_5 | token_6 ) ) [_val = bind(binary_pow, _val, _1)];
//
//    token_6 = ( ( '(' >> expression  >> ')'                                           ) [_val = _1            ]
//              | (        token_fun_0 >> '(' >> ')'                                    ) [_val = bind(_1)      ]
//              | (        token_fun_1 >> '(' >> expression >> ')'                      ) [_val = bind(_1,_2)   ]
//              | (        token_fun_2 >> '(' >> expression >> ',' >> expression >> ')' ) [_val = bind(_1,_2,_3)]
//              | (        token_con                                                    ) [_val = _1            ] );
//
//    token_6_p =   (                    token_6   ) [_val = _1                        ]
//              >> -( '^' >> ( token_5 | token_6 ) ) [_val = bind(binary_pow, _val, _1)];
//}

template < class type >
type numeric_expr<type>::operator() ( const string& str ) const
{
    using namespace boost::spirit::qi;

    // Calculate.
    auto  pos     = str.begin();
    auto  result  = type();
    bool success = phrase_parse(pos, str.end(), self.expression, ascii::space, result);

    if ( success and pos == str.end() )
        return result;
    else
        throw parse_error("failed to parse numeric_expr \"{}\" at pos {} (with attriande = {})", str, pos-str.begin()+1, typeid(type));
}

template < class type >
map_type auto& numeric_expr<type>::constant ( )
{
    return static_cast<map<string,type>&>(*token_con.lookup);
}

template < class type >
const map_type auto& numeric_expr<type>::constant ( ) const
{
    return static_cast<const map<string,type>&>(*token_con.lookup);
}

template < class type >
map_type auto& numeric_expr<type>::nullary_function ( )
{
    return static_cast<map<string,function<type()>>&>(*token_fun_0.lookup);
}

template < class type >
const map_type auto& numeric_expr<type>::nullary_function ( ) const
{
    return static_cast<const map<string,function<type()>>&>(*token_fun_0.lookup);
}

template < class type >
map_type auto& numeric_expr<type>::unary_function ( )
{
    return static_cast<map<string,function<type(type)>>&>(*token_fun_1.lookup);
}

template < class type >
const map_type auto& numeric_expr<type>::unary_function ( ) const
{
    return static_cast<const map<string,function<type(type)>>&>(*token_fun_1.lookup);
}

template < class type >
map_type auto& numeric_expr<type>::binary_function ( )
{
    return static_cast<map<string,function<type(type,type)>>&>(*token_fun_2.lookup);
}

template < class type >
const map_type auto& numeric_expr<type>::binary_function ( ) const
{
    return static_cast<const map<string,function<type(type,type)>>&>(*token_fun_2.lookup);
}

template < class type >
type numeric_expr<type>::binary_multiply ( const type& a, const type& b )
{
    return a * b;
}

template < class type >
type numeric_expr<type>::binary_pow ( const type& a, const type& b )
{
    return pow(a, b);
}






/// Class numeric_expr<type(type)>::var_con_map

template < class type >
template < int index >
class numeric_expr<type(type)>::var_con_map
{
    private: // Data
        string*              ptr_var  = nullptr;
        map<string,type>*    ptr_con  = nullptr;
        function<type(type)> make_var = [] (const auto& x) { return x; };

    public: // Interface
        function<type(type)>* find ( const char*& ptr_begin, const char* ptr_end, auto )
            requires ( index == 1 )
        {
            for ( auto ptr in range ( ptr_end, ptr_begin + 1, -1 ) )
                if ( *ptr_var == string_view(ptr_begin, ptr) )
                {
                    ptr_begin = ptr;
                    return &make_var;
                }
                else if ( ptr_con->keys().contains(string_view(ptr_begin, ptr)) )
                    break;
            return nullptr;
        }

        const function<type(type)>* find ( const char*& ptr_begin, const char* ptr_end, auto ) const
            requires ( index == 1 )
        {
            for ( auto ptr in range ( ptr_end, ptr_begin + 1, -1 ) )
                if ( *ptr_var == string_view(ptr_begin, ptr) )
                {
                    ptr_begin = ptr;
                    return &make_var;
                }
                else if ( ptr_con->keys().contains(string_view(ptr_begin, ptr)) )
                    break;
            return nullptr;
        }

        type* find ( const char*& ptr_begin, const char* ptr_end, auto )
            requires ( index == 2 )
        {
            for ( auto ptr in range ( ptr_end, ptr_begin + 1, -1 ) )
                if ( ptr_con->keys().contains(string_view(ptr_begin, ptr)) )
                {
                    auto& v = (*ptr_con)[string_view(ptr_begin, ptr)];
                    ptr_begin = ptr;
                    return &v;
                }
                else if ( *ptr_var == string_view(ptr_begin, ptr) )
                    break;
            return nullptr;
        }

        const type* find ( const char*& ptr_begin, const char* ptr_end, auto ) const
            requires ( index == 2 )
        {
            for ( auto ptr in range ( ptr_end, ptr_begin + 1, -1 ) )
                if ( ptr_con->keys().contains(string_view(ptr_begin, ptr)) )
                {
                    auto& v = (*ptr_con)[string_view(ptr_begin, ptr)];
                    ptr_begin = ptr;
                    return &v;
                }
                else if ( *ptr_var == string_view(ptr_begin, ptr) )
                    break;
            return nullptr;
        }

        void link ( string& target_var, map<string,type>& target_con )
        {
            ptr_var = &target_var;
            ptr_con = &target_con;
        }
};



/// Class numeric_expr<type(type)>

template < class type >
numeric_expr<type(type)>::numeric_expr ( )
    extends expression ( token_1 )
{
    using namespace boost::spirit::qi;
    using namespace boost::phoenix;

    token_1 =   ( (        token_2 ) [_val = _1                          ]
                | ( '+' >> token_2 ) [_val = bind(unary_add, _1)         ]
                | ( '-' >> token_2 ) [_val = bind(unary_minus, _1)       ] )
            >> *( ( '+' >> token_2 ) [_val = bind(binary_add, _val, _1)  ]
                | ( '-' >> token_2 ) [_val = bind(binary_minus, _val, _1)] );

    token_2 =   (          token_3 ) [_val = _1                             ]
            >> *( ( '*' >> token_3 ) [_val = bind(binary_multiply, _val, _1)]
                | ( '/' >> token_3 ) [_val = bind(binary_divide, _val, _1)  ] );

    token_3 =   (        token_4 ) [_val = _1                        ]
            >> -( '^' >> token_4 ) [_val = bind(binary_pow, _val, _1)];

    token_4 = ( ( token_5   >> token_6_p ) [_val = bind(binary_multiply, _1, _2)]
              | ( token_5_p |  token_6_p ) [_val = _1                           ] );

    token_5 = type_ [_val = bind(make_con, _1)];

    token_5_p =   (          token_5             ) [_val = _1                 ]
              >> -( '^' >> ( token_5 | token_6 ) ) [_val = bind(binary_pow, _val, _1)];

    token_6 = ( ( '(' >> expression  >> ')'                                           ) [_val = _1                        ]
              | (        token_fun_0 >> '(' >> ')'                                    ) [_val = bind(make_fun_0, _1)      ]
              | (        token_fun_1 >> '(' >> expression >> ')'                      ) [_val = bind(make_fun_1, _1,_2)   ]
              | (        token_fun_2 >> '(' >> expression >> ',' >> expression >> ')' ) [_val = bind(make_fun_2, _1,_2,_3)]
              | (        token_var                                                    ) [_val = _1                        ]
              | (        token_con                                                    ) [_val = bind(make_con, _1)        ] );

    token_6_p =   (                    token_6   ) [_val = _1                        ]
              >> -( '^' >> ( token_5 | token_6 ) ) [_val = bind(binary_pow, _val, _1)];


    token_var.lookup->link(var, con);
    token_con.lookup->link(var, con);
}

template < class type >
function<type(type)> numeric_expr<type(type)>::operator() ( const string& str ) const
{
    using namespace boost::spirit::qi;

    // Calculate.
    auto  pos     = str.begin();
    auto  result  = function<type(type)>();
    bool success = phrase_parse(pos, str.end(), self.expression, ascii::space, result);
    if ( success and pos == str.end() )
        return result;
    else
        throw parse_error("failed to parse numeric_expr \"{}\" at pos {} (with attriande = {})", str, pos-str.begin()+1, typeid(type(type)));
}

template < class type >
string_type auto& numeric_expr<type(type)>::variable ( )
{
    return var;
}

template < class type >
const string_type auto& numeric_expr<type(type)>::variable ( ) const
{
    return var;
}

template < class type >
map_type auto& numeric_expr<type(type)>::constant ( )
{
    return con;
}

template < class type >
const map_type auto& numeric_expr<type(type)>::constant ( ) const
{
    return con;
}

template < class type >
map_type auto& numeric_expr<type(type)>::nullary_function ( )
{
    return static_cast<map<string,function<type()>>&>(*token_fun_0.lookup);
}

template < class type >
const map_type auto& numeric_expr<type(type)>::nullary_function ( ) const
{
    return static_cast<const map<string,function<type()>>&>(*token_fun_0.lookup);
}

template < class type >
map_type auto& numeric_expr<type(type)>::unary_function ( )
{
    return static_cast<map<string,function<type(type)>>&>(*token_fun_1.lookup);
}

template < class type >
const map_type auto& numeric_expr<type(type)>::unary_function ( ) const
{
    return static_cast<const map<string,function<type(type)>>&>(*token_fun_1.lookup);
}

template < class type >
map_type auto& numeric_expr<type(type)>::binary_function ( )
{
     return static_cast<map<string,function<type(type,type)>>&>(*token_fun_2.lookup);
}

template < class type >
const map_type auto& numeric_expr<type(type)>::binary_function ( ) const
{
    return static_cast<const map<string,function<type(type,type)>>&>(*token_fun_2.lookup);
}

template < class type >
function<type(type)> numeric_expr<type(type)>::make_con ( const type& a )
{
    return [=] (const auto&) { return a; };
}

template < class type >
function<type(type)> numeric_expr<type(type)>::make_fun_0 ( const function<type()>& a )
{
    return [=] (const auto&) { return a(); };
}

template < class type >
function<type(type)> numeric_expr<type(type)>::make_fun_1 ( const function<type(type)>& a, const function<type(type)>& b )
{
    return [=] (const auto& x) { return a(b(x)); };
}

template < class type >
function<type(type)> numeric_expr<type(type)>::make_fun_2 ( const function<type(type,type)>& a, const function<type(type)>& b, const function<type(type)>& c )
{
    return [=] (const auto& x) { return a(b(x), c(x)); };
}

template < class type >
function<type(type)> numeric_expr<type(type)>::unary_add ( const function<type(type)>& a )
{
    return [=] (const auto& x) { return +a(x); };
}

template < class type >
function<type(type)> numeric_expr<type(type)>::unary_minus ( const function<type(type)>& a )
{
    return [=] (const auto& x) { return -a(x); };
}

template < class type >
function<type(type)> numeric_expr<type(type)>::binary_add ( const function<type(type)>& a, const function<type(type)>& b )
{
    return [=] (const auto& x) { return a(x) + b(x); };
}

template < class type >
function<type(type)> numeric_expr<type(type)>::binary_minus ( const function<type(type)>& a, const function<type(type)>& b )
{
    return [=] (const auto& x) { return a(x) - b(x); };
}

template < class type >
function<type(type)> numeric_expr<type(type)>::binary_multiply ( const function<type(type)>& a, const function<type(type)>& b )
{
    return [=] (const auto& x) { return a(x) * b(x); };
}

template < class type >
function<type(type)> numeric_expr<type(type)>::binary_divide ( const function<type(type)>& a, const function<type(type)>& b )
{
    return [=] (const auto& x) { return a(x) / b(x); };
}

template < class type >
function<type(type)> numeric_expr<type(type)>::binary_pow ( const function<type(type)>& a, const function<type(type)>& b )
{
    return [=] (const auto& x) { return pow(a(x), b(x)); };
}





/// Class numeric_expr<type(type,type)>::var_con_map

template < class type >
template < int index >
class numeric_expr<type(type,type)>::var_con_map
{
    private: // Data
        pair<string,string>*      ptr_var    = nullptr;
        map<string,type>*         ptr_con    = nullptr;
        function<type(type,type)> make_var_1 = [] (const auto& x, const auto&) { return x; };
        function<type(type,type)> make_var_2 = [] (const auto&, const auto& y) { return y; };

    public: // Interface
        function<type(type,type)>* find ( const char*& ptr_begin, const char* ptr_end, auto )
            requires ( index == 1 )
        {
            for ( auto ptr in range ( ptr_end, ptr_begin + 1, -1 ) )
                if ( ptr_var->key() == string_view(ptr_begin, ptr) )
                {
                    ptr_begin = ptr;
                    return &make_var_1;
                }
                else if ( ptr_var->value() == string_view(ptr_begin, ptr) )
                {
                    ptr_begin = ptr;
                    return &make_var_2;
                }
                else if ( ptr_con->keys().contains(string_view(ptr_begin, ptr)) )
                    break;
            return nullptr;
        }

        const function<type(type,type)>* find ( const char*& ptr_begin, const char* ptr_end, auto ) const
            requires ( index == 1 )
        {
            for ( auto ptr in range ( ptr_end, ptr_begin + 1, -1 ) )
                if ( ptr_var->key() == string_view(ptr_begin, ptr) )
                {
                    ptr_begin = ptr;
                    return &make_var_1;
                }
                else if ( ptr_var->value() == string_view(ptr_begin, ptr) )
                {
                    ptr_begin = ptr;
                    return &make_var_2;
                }
                else if ( ptr_con->keys().contains(string_view(ptr_begin, ptr)) )
                    break;
            return nullptr;
        }

        type* find ( const char*& ptr_begin, const char* ptr_end, auto )
            requires ( index == 2 )
        {
            for ( auto ptr in range ( ptr_end, ptr_begin + 1, -1 ) )
                if ( ptr_con->keys().contains(string_view(ptr_begin, ptr)) )
                {
                    auto& v = (*ptr_con)[string_view(ptr_begin, ptr)];
                    ptr_begin = ptr;
                    return &v;
                }
                else if ( ptr_var->key() == string_view(ptr_begin, ptr) or ptr_var->value() == string_view(ptr_begin, ptr) )
                    break;
            return nullptr;
        }

        const type* find ( const char*& ptr_begin, const char* ptr_end, auto ) const
            requires ( index == 2 )
        {
            for ( auto ptr in range ( ptr_end, ptr_begin + 1, -1 ) )
                if ( ptr_con->keys().contains(string_view(ptr_begin, ptr)) )
                {
                    auto& v = (*ptr_con)[string_view(ptr_begin, ptr)];
                    ptr_begin = ptr;
                    return &v;
                }
                else if ( ptr_var->key() == string_view(ptr_begin, ptr) or ptr_var->value() == string_view(ptr_begin, ptr) )
                    break;
            return nullptr;
        }

        void link ( pair<string>& target_var, map<string,type>& target_con )
        {
            ptr_var = &target_var;
            ptr_con = &target_con;
        }
};



/// Class numeric_expr<type(type)>

template < class type >
numeric_expr<type(type,type)>::numeric_expr ( )
    extends expression ( token_1 )
{
    using namespace boost::spirit::qi;
    using namespace boost::phoenix;

    token_1 =   ( (        token_2 ) [_val = _1                          ]
                | ( '+' >> token_2 ) [_val = bind(unary_add, _1)         ]
                | ( '-' >> token_2 ) [_val = bind(unary_minus, _1)       ] )
            >> *( ( '+' >> token_2 ) [_val = bind(binary_add, _val, _1)  ]
                | ( '-' >> token_2 ) [_val = bind(binary_minus, _val, _1)] );

    token_2 =   (          token_3 ) [_val = _1                             ]
            >> *( ( '*' >> token_3 ) [_val = bind(binary_multiply, _val, _1)]
                | ( '/' >> token_3 ) [_val = bind(binary_divide, _val, _1)  ] );

    token_3 =   (        token_4 ) [_val = _1                        ]
            >> -( '^' >> token_4 ) [_val = bind(binary_pow, _val, _1)];

    token_4 = ( ( token_5   >> token_6_p ) [_val = bind(binary_multiply, _1, _2)]
              | ( token_5_p | token_6_p  ) [_val = _1                           ] );

    token_5 = type_ [_val = bind(make_con, _1)];

    token_5_p =   (          token_5             ) [_val = _1                        ]
              >> -( '^' >> ( token_5 | token_6 ) ) [_val = bind(binary_pow, _val, _1)];

    token_6 = ( ( '(' >> expression  >> ')'                                           ) [_val = _1                        ]
              | (        token_fun_0 >> '(' >> ')'                                    ) [_val = bind(make_fun_0, _1)      ]
              | (        token_fun_1 >> '(' >> expression >> ')'                      ) [_val = bind(make_fun_1, _1,_2)   ]
              | (        token_fun_2 >> '(' >> expression >> ',' >> expression >> ')' ) [_val = bind(make_fun_2, _1,_2,_3)]
              | (        token_var                                                    ) [_val = _1                        ]
              | (        token_con                                                    ) [_val = bind(make_con, _1)        ] );

    token_6_p =   (                    token_6   ) [_val = _1                        ]
              >> -( '^' >> ( token_5 | token_6 ) ) [_val = bind(binary_pow, _val, _1)];

    token_var.lookup->link(var, con);
    token_con.lookup->link(var, con);
}

template < class type >
function<type(type,type)> numeric_expr<type(type,type)>::operator() ( const string& str ) const
{
    using namespace boost::spirit::qi;

    // Calculate.
    auto  pos     = str.begin();
    auto  result  = function<type(type,type)>();
    bool success = phrase_parse(pos, str.end(), self.expression, ascii::space, result);
    if ( success and pos == str.end() )
        return result;
    else
        throw parse_error("failed to parse numeric_expr \"{}\" at pos {} (with attriande = {})", str, pos-str.begin()+1, typeid(type(type,type)));
}

template < class type >
pair_type auto& numeric_expr<type(type,type)>::variable ( )
{
    return var;
}

template < class type >
const pair_type auto& numeric_expr<type(type,type)>::variable ( ) const
{
    return var;
}

template < class type >
map_type auto& numeric_expr<type(type,type)>::constant ( )
{
    return con;
}

template < class type >
const map_type auto& numeric_expr<type(type,type)>::constant ( ) const
{
    return con;
}

template < class type >
map_type auto& numeric_expr<type(type,type)>::nullary_function ( )
{
    return static_cast<map<string,function<type()>>&>(*token_fun_0.lookup);
}

template < class type >
const map_type auto& numeric_expr<type(type,type)>::nullary_function ( ) const
{
    return static_cast<const map<string,function<type()>>&>(*token_fun_0.lookup);
}

template < class type >
map_type auto& numeric_expr<type(type,type)>::unary_function ( )
{
    return static_cast<map<string,function<type(type)>>&>(*token_fun_1.lookup);
}

template < class type >
const map_type auto& numeric_expr<type(type,type)>::unary_function ( ) const
{
    return static_cast<const map<string,function<type(type)>>&>(*token_fun_1.lookup);
}

template < class type >
map_type auto& numeric_expr<type(type,type)>::binary_function ( )
{
     return static_cast<map<string,function<type(type,type)>>&>(*token_fun_2.lookup);
}

template < class type >
const map_type auto& numeric_expr<type(type,type)>::binary_function ( ) const
{
    return static_cast<const map<string,function<type(type,type)>>&>(*token_fun_2.lookup);
}

template < class type >
function<type(type,type)> numeric_expr<type(type,type)>::make_con ( const type& a )
{
    return [=] (const auto&, const auto&) { return a; };
}

template < class type >
function<type(type,type)> numeric_expr<type(type,type)>::make_fun_0 ( const function<type()>& a )
{
    return [=] (const auto&, const auto&) { return a(); };
}

template < class type >
function<type(type,type)> numeric_expr<type(type,type)>::make_fun_1 ( const function<type(type)>& a, const function<type(type,type)>& b )
{
    return [=] (const auto& x, const auto& y) { return a(b(x, y)); };
}

template < class type >
function<type(type,type)> numeric_expr<type(type,type)>::make_fun_2 ( const function<type(type,type)>& a, const function<type(type,type)>& b, const function<type(type,type)>& c )
{
    return [=] (const auto& x, const auto& y) { return a(b(x, y), c(x, y)); };
}

template < class type >
function<type(type,type)> numeric_expr<type(type,type)>::unary_add ( const function<type(type,type)>& a )
{
    return [=] (const auto& x, const auto& y) { return +a(x, y); };
}

template < class type >
function<type(type,type)> numeric_expr<type(type,type)>::unary_minus ( const function<type(type,type)>& a )
{
    return [=] (const auto& x, const auto& y) { return -a(x, y); };
}

template < class type >
function<type(type,type)> numeric_expr<type(type,type)>::binary_add ( const function<type(type,type)>& a, const function<type(type,type)>& b )
{
    return [=] (const auto& x, const auto& y) { return a(x, y) + b(x, y); };
}

template < class type >
function<type(type,type)> numeric_expr<type(type,type)>::binary_minus ( const function<type(type,type)>& a, const function<type(type,type)>& b )
{
    return [=] (const auto& x, const auto& y) { return a(x, y) - b(x, y); };
}

template < class type >
function<type(type,type)> numeric_expr<type(type,type)>::binary_multiply ( const function<type(type,type)>& a, const function<type(type,type)>& b )
{
    return [=] (const auto& x, const auto& y) { return a(x, y) * b(x, y); };
}

template < class type >
function<type(type,type)> numeric_expr<type(type,type)>::binary_divide ( const function<type(type,type)>& a, const function<type(type,type)>& b )
{
    return [=] (const auto& x, const auto& y) { return a(x, y) / b(x, y); };
}

template < class type >
function<type(type,type)> numeric_expr<type(type,type)>::binary_pow ( const function<type(type,type)>& a, const function<type(type,type)>& b )
{
    return [=] (const auto& x, const auto& y) { return pow(a(x, y), b(x, y)); };
}