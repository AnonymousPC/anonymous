import anonymous;
import std;
import boost;
import cuda;
import thrust;
using namespace anonymous;

void sort ( int*, int*, predicate<int> auto )
{

}


// int main()
// {
//     auto stream = http_stream();
//     stream.listen("http://127.0.0.1:33210");

//     auto response1 = string();
//     auto task1 = std::execution::just(std::move(stream1))
//                | std::execution::let_value([] (auto&& stream1)
//                    {
//                        return stream1 > response1;
//                    })
//                | std::execution::let_value([] (auto&& stream2)
//                    {
//                        return stream1 < response1;     
//                    });
//     auto response2 = string();
//     auto task2 = std::execution::just(std::move(stream2))
//                | std::execution::let_value([] (auto&& stream2)
//                    {
//                        return stream2 > response2;
//                    });
//     std::execution::sync_wait(std::execution::when_all(task1, task2));
// }