import anonymous;
import std;
import boost;
import cuda;
import thrust;

using namespace anonymous;

int main () 
{
    auto arr = array<int,2,anonymous::cuda>{{1, 2, 3}, {4, 5, 6}};
    for ( auto val in arr.flatten() )
        print(val);

    print("==========");

    auto arr2 = array<int,2>(arr);
    for ( auto val in arr2.flatten() )
        print(val);
}
