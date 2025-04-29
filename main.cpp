import anonymous;
import std;
import stdexec;
import plf;
import boost;
import Eigen;
using namespace anonymous;

int main ( )
{
    print(variant<int,double>(2.3).template value<2>());
}
