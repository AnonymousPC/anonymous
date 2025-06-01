import anonymous;
import std;
import boost;
import Eigen;
#include <__mdspan/>

int main ( )
{
    my_namespace::my_class a;

    std::println("1");
    swap(a, a);


    swap(my_namespace::my_class, my_namespace::my_class); // 不存在::swap

    std::println("2");

    my_namespace::swap(a, a);

    std::println("3");
    std::swap(a, a);

    
}
