#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
#include "specific/audio/interface.hpp"
#include "specific/neural/interface.hpp"
#include "specific/spirit/interface.hpp"
#include "specific/stock/interface.hpp"

using namespace ap;

struct noisy
{
    noisy() = default;
    noisy(const noisy&)            { print("copy construct"); }
    noisy(noisy&&)                 { print("move construct"); }
    noisy& operator=(const noisy&) { print("copy assign"); return self; }
    noisy& operator=(noisy&&)      { print("move assign"); return self; }
};

struct my_iterator
{
    int val = 0;

    my_iterator() = default;
    my_iterator(int v) extends val(v) {};
   ~my_iterator() { print("~iterator"); }
    
    int& operator*() { return val; };
    my_iterator& operator++()    { ++val; return self; }
    my_iterator  operator++(int) { let it = self; ++self; return it; }

    friend bool operator == (const my_iterator&, const my_iterator&) = default;
};

struct my_class
{
    auto begin ( ) const { return my_iterator(0); };
    auto end   ( ) const { return my_iterator(10); };
};

int main ( )
{
    my_class obj;
    for ( auto& o in obj )
        print(&o);
}