import anonymous;
import std;
import stdexec;
import plf;
import boost;
import Eigen;
using namespace anonymous;

int main ( )
{
    auto a = array<int,2,opencl>(2, 3);
    print(a);
}