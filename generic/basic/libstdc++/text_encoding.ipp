
std::text_encoding std::text_encoding::environment ( )
{
    #ifdef _WIN32
        return std::text_encoding::GBK;
    #elifdef __APPLE__
        return std::text_encoding::UTF8;
    #else
        return std::text_encoding::unknown;
    #endif
};