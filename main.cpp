import anonymous;
import std;
import stdexec;
import plf;
import boost;
import Eigen;
using namespace anonymous;

int main ( )
{
    auto v = std::vector<int>(100);
    int* p = nullptr;
    auto mds = std::mdspan(p, std::dextents<int,3>(2, 3, 4));
    print(mds.mapping()(10, 1, 1));
}