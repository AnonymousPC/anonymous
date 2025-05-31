export namespace std{

template <class _Layout>
struct layout_transpose {
    template <class _Extents> class mapping;
};

template <class _Layout>
template <class _Extents>
class layout_transpose<_Layout>::mapping
{
    static_assert(false, "should be specialized");  
};

template <>
struct layout_transpose<layout_right>
{
    template <class _Extents> using mapping = layout_left::template mapping<_Extents>;
};

template <>
struct layout_transpose<layout_left>
{
    template <class _Extents> using mapping = layout_right::template mapping<_Extents>;
};
    
} // namespace std
