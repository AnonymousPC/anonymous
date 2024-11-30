#include "../generic/basic/interface.hpp"
#include "../generic/container/interface.hpp"
#include "../generic/io/interface.hpp"
#include "../generic/math/interface.hpp"
#include "../specific/audio/interface.hpp"
#include "../specific/neural/interface.hpp"
#include "../specific/spirit/interface.hpp"
#include "../specific/stock/interface.hpp"
#include "example.cpp"
using namespace ap;

template < class type >
concept my_concept = requires { type::good(); };

template < class type >
    requires std::copyable<type>
class my_class
    extends public pair<int,double>
{
    int a = my_concept<int> ? 1 : 0;

    my_class()
    { this->self;
    self.operator=(global_gpu_context.get_scheduler());
        self.a = 1;
        let b = 2;
    }

    virtual void define ( ) = abstract;

    void good()
    {
        let a = array<int>{1,2,3};
        self.run();
        return self;
        
    }
}；