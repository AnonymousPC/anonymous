namespace detail
{
    auto stringalize_array ( std::ostream& stream, const auto& arr )
    {
        return stringalize_array(stream, arr, [&] (const auto& item)
                   {
                       auto buff = std::stringstream();
                       buff.copyfmt(stream);
                       buff << item;
                       return buff.str(); 
                   });
    }

    auto stringalize_array ( std::ostream& stream, const auto& arr, const auto& stringalizer )
    {
        if constexpr ( arr.dimension() == 1 )
            return array<std::string,arr.dimension()>(arr.size(), [&] (int i) { return stringalizer(arr[i]); } );
        else
        {
            auto string_array = array<std::string,arr.dimension()>();
            string_array.resize(arr.shape());
            for ( int i in range(arr.shape()[1]) )
                string_array[i] = stringalize_array(stream, arr[i], stringalizer);
            return string_array;
        }
    }

    void align_array ( auto& arr )
    {
        if constexpr ( arr.dimension() == 1 )
        {
            auto align = arr.empty() ? 0 : arr.max([] (const auto& str1, const auto& str2) { return str1.size() < str2.size(); }).size();

            arr.for_each([&] (auto& str) { str.resize(align, ' '); });
        }
        else
        {
            auto align = arr.empty() ? 0 : arr.flatten().max([] (const auto& str1, const auto& str2) { return str1.size() < str2.size(); }).size();

            arr.flatten()
               .for_each([&] (auto& str) { str.resize(align, ' '); });
        }
    }

    void print_array ( auto& stream, const auto& arr, int dep = 1 )
    {
        stream << '{';

        if constexpr ( arr.dimension() == 1 )
            for ( int i in range(arr.size()) )
            {
                stream << arr[i];
                if ( i < arr.size() )
                    stream << ' ';
            }

        else
            for ( int i in range(arr.shape()[1]) )
            {
                print_array(stream, arr[i], dep + 1);
                if ( i != arr.shape()[1] )
                {
                    stream << ' ';
                    for ( int _ in range(arr.dimension() - 1) )
                        stream << '\n';
                    for ( int _ in range(dep) )
                        stream << ' ';
                }
            }

        stream << '}';
    }

}