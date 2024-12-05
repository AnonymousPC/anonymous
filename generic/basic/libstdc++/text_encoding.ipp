
std::text_encoding std::text_encoding::environment ( )
{
    #ifdef system_windows
        return std::text_encoding::GBK;
    #elifdef system_linux
        return std::text_encoding::UTF8;
    #elifdef system_mac
        return std::text_encoding::UTF8;
    #else
        return std::text_encoding::unknown;
    #endif
};