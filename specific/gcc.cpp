#include <iostream>
#include <boost/locale.hpp>
#include <vector>
#include <ranges>

int main()
{
    std::string a = "中文";
    std::string b = boost::locale::conv::between(a, "UTF-8", "GBK", boost::locale::conv::stop);

}