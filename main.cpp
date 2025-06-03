import anonymous;
import std;
import boost;
import Eigen;
import thrust;
using namespace anonymous;

int main ( )
{
    auto vct1 = vector<float>(10);
    auto vct2 = vector<std::complex<float>>(10);
    cpu::fft(vct1.mdspan().template value<1>(), vct2.mdspan().template value<1>());
}


