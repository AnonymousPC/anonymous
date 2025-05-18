struct pipe_buf::environment     extends public detail::io_mode<map<string,array<string>>> { using detail::io_mode<map<string,array<string>>>::io_mode; struct pipe_mode_tag { }; };
struct pipe_buf::param           extends public detail::io_mode<array<string>>             { using detail::io_mode<array<string>>            ::io_mode; struct pipe_mode_tag { }; };
struct pipe_buf::start_directory extends public detail::io_mode<path>                      { using detail::io_mode<path>                     ::io_mode; struct pipe_mode_tag { }; };

template < >
struct pipe_buf::tuple<>
{
    constexpr static const int size = 0;
};

template < class type, class... types >
struct pipe_buf::tuple<type,types...>
{
    type            first;
    tuple<types...> other;
    constexpr tuple ( type, types... );
    constexpr static const int size = 1 + sizeof...(types);
};

void pipe_buf::open ( path exe, pipe_mode auto... args )
{
    // Check.
    if constexpr ( sizeof...(args) >= 1 )
        static_assert(detail::all_different<decltype(args)...>, "modes must be unique");

    // Find executable.
    auto path_executable = boost::filesystem::path(exe.c_str());
    auto find_executable = boost::process::v2::environment::find_executable(exe.c_str());

    // Open pipe.
    try
    {
        // Find_executable is always in higher priority than raw_path.
        handle = run_with_args(find_executable != "" ? find_executable : path_executable, {}, tuple<decltype(args)...>(args...));
    }
    catch ( const boost::process::v2::system_error& e )
    {
        throw pipe_error("open failed (with path_executable = {}, find_executable = {})", exe, boost::filesystem::is_regular_file(path_executable) ? path_executable : "[[not exist]]", find_executable != "" ? find_executable : "[[not found]]").from(detail::system_error(e));
    }

    // Set put area.
    setp(stdin_buff.data(),
         stdin_buff.data() + stdin_buff.size());
}

// Auxiliary

auto pipe_buf::run_with_args ( const boost::filesystem::path& proc, std::vector<std::string> params, const auto& inputs, auto... outputs )
{
    if constexpr ( decay<decltype(inputs)>::size == 0 )
        return std::make_unique<boost::process::v2::process>(boost::asio::system_executor(), proc, params, outputs..., boost::process::v2::process_stdio(stdin_pipe, stdout_pipe, stderr_pipe));

    else if constexpr ( same_as<decltype(inputs.first),environment> )
    {
        auto env = boost::process::v2::process_environment(inputs.first.value
                | std::views::transform([] (const auto& kv)
                                        {
                                            auto k = std::string(kv.key());
                                            auto v = std::string(kv.value()
                                                  | std::views::join_with(char_type(';'))
                                                  | std::ranges::to<std::string>());
                                            return std::pair(k, v);
                                        })
                | std::ranges::to<std::map<std::string,std::string>>());
        return run_with_args(proc, params, inputs.other, env, outputs...);
    }

    else if constexpr ( same_as<decltype(inputs.first),param> )
    {
        params = inputs.first.value
               | std::views::transform([] (const auto& prm) { return std::string(prm); })
               | std::ranges::to<std::vector<std::string>>();
        return run_with_args(proc, params, inputs.other, outputs...);
    }

    else if constexpr ( same_as<decltype(inputs.first),start_directory> )
    {
        auto startdir = boost::process::v2::process_start_dir(inputs.first.value.c_str());
        return run_with_args(proc, params, inputs.other, startdir, outputs...);
    }

    else
        return run_with_args(proc, params, inputs.other, outputs...);
}

template < class type, class... types >
constexpr pipe_buf::tuple<type,types...>::tuple ( type arg1, types... args )
    extends first ( std::forward<decltype(arg1)>(arg1) ),
            other ( std::forward<decltype(args)>(args)... )
{

}