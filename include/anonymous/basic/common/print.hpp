class print_t
{
    public:
        constexpr static void operator() (  const printable auto&... );
};

#include "print.cpp"

