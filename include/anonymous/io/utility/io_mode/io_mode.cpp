// template 

template < class type >
constexpr detail::io_mode<type>::io_mode ( type v )
    extends value ( v )
{

}

// string

constexpr detail::io_mode<string>::io_mode ( string v )
    extends value ( v )
{
    
}

// pair<string,string>

constexpr detail::io_mode<pair<string,string>>::io_mode ( string k, string v )
    extends value ( k, v )
{
    
}

constexpr detail::io_mode<pair<string,string>>::io_mode ( pair<string,string> kv )
    extends value ( kv )
{
    
}

// array<string>

constexpr detail::io_mode<array<string>>::io_mode ( string v )
    extends value { v }
{
    
}

constexpr detail::io_mode<array<string>>::io_mode ( array<string> v )
    extends value ( v )
{
    
}

constexpr detail::io_mode<array<string>>::io_mode ( string v1, convertible_to<string> auto... vs )
    extends value { v1, string(vs)... }
{

}

// map<string,string>

constexpr detail::io_mode<map<string,string>>::io_mode ( string k, string v )
    extends value { {k, v} }
{
    
}

constexpr detail::io_mode<map<string,string>>::io_mode ( pair<string,string> kv )
    extends value { kv }
{
    
}

constexpr detail::io_mode<map<string,string>>::io_mode ( map<string,string> m )
    extends value { m }
{

}

// map<string,array<string>>

constexpr detail::io_mode<map<string,array<string>>>::io_mode ( string k, string v )
    extends value ( { {k, {v}} } )
{

}

constexpr detail::io_mode<map<string,array<string>>>::io_mode ( string k, array<string> v )
extends value ( { {k, v} } )
{

}

constexpr detail::io_mode<map<string,array<string>>>::io_mode ( pair<string,string> kv )
extends value ( { {kv.key(), {kv.value()}} } )
{

}

constexpr detail::io_mode<map<string,array<string>>>::io_mode ( pair<string,array<string>> kv )
extends value ( { {kv.key(), kv.value()} } )
{

}

constexpr detail::io_mode<map<string,array<string>>>::io_mode ( map<string,string> m )
    extends value ( m | std::views::transform([] (const auto& kv) { return pair<string,array<string>>(kv.key(), {kv.value()}); })
                      | std::ranges::to<map<string,array<string>>>() )
{

}

constexpr detail::io_mode<map<string,array<string>>>::io_mode ( map<string,array<string>> m )
    extends value ( m )
{

}


