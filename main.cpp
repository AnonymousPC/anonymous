import anonymous;
import std;
import boost;
import cuda;
import thrust;

using namespace anonymous;

int main () 
{
    auto init = {1, 2, 3, 4, 5};
    static_assert(same_as<decltype(init),std::initializer_list<int>>);
    

}

