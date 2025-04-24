import anonymous;
import std;
import stdexec;
import plf;
import boost;
import Eigen;
using namespace anonymous;

struct test
{
    constexpr int dimension() const { return 1; }
    using value_type = double;
};

constexpr auto func ( const auto v )
    requires ( same_as<typename decltype(v)::value_type,double> )
{
    return "Hello";
}

int main ( )
{
    auto mds = std::mdspan<int,std::dextents<int,1>>();
    print(mds.rank());
}
