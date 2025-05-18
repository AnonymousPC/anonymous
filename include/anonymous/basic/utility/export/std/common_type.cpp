template < >
struct common_type<anonymous::cpu,anonymous::cpu>
{
    using type = anonymous::cpu;
};

template < class device >
struct common_type<anonymous::cpu,device>
{
    using type = device;
};

template < class device >
struct common_type<device,anonymous::cpu>
{
    using type = device;
};