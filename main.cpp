import anonymous;
import std;
import boost;
import thrust.tbb;
using namespace anonymous;

int main ( )
{
    std::println("good");

    thrust::device_vector<int> vct(10);
    thrust::sort(vct.begin(), vct.end());
}