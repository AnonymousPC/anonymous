constexpr void sleep ( duration time )
{
    sleep_for(time);
}

constexpr void sleep_for ( duration time )
{
    std::this_thread::sleep_for(std::chrono::nanoseconds(time));
}

constexpr void sleep_until ( time_point time )
{
    sleep_for(time - now());
}

constexpr int time_zone ( )
{
    return (boost::posix_time::second_clock::local_time() - boost::posix_time::second_clock::universal_time()).hours();
}