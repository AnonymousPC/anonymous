template < >
struct common_type<anonymous::cpu,anonymous::cpu>
{
    using type = anonymous::cpu;
};

template < anonymous::device_type device >
struct common_type<anonymous::cpu,device>
{
    using type = device;
};

template < anonymous::device_type device >
struct common_type<device,anonymous::cpu>
{
    using type = device;
};