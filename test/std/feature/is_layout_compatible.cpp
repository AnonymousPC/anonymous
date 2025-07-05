import std;

struct a
{
    [[maybe_unused]] int x;
    [[maybe_unused]] char y;
};
 
struct b
{
    [[maybe_unused]] int x;
    [[maybe_unused]] [[no_unique_address]] char y;
};
 
class c
{
    [[maybe_unused]] const int u = 42;
    [[maybe_unused]] volatile char v = '*';
};
 
enum d 
    extends int
{

};

enum class e 
    extends int 
{

};
 
// static_assert(    std::is_layout_compatible<const void, volatile void>::value);
static_assert(    std::is_layout_compatible<a, c>::value);
// static_assert(not std::is_layout_compatible<a[2], c[2]>::value);
// static_assert(not std::is_layout_compatible<int, d>::value);
static_assert(    std::is_layout_compatible<d, e>::value);
// static_assert(not std::is_layout_compatible<long, unsigned long>::value);
// static_assert(not std::is_layout_compatible<char*, const char*>::value);
static_assert(    std::is_layout_compatible<char*, char* const>::value);
// static_assert(not std::is_layout_compatible<a, b>::value);

int main ( )
{

}