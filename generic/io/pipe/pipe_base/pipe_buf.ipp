#pragma once

/// Subclass

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



/// Class pipe_buf

// Interface

void pipe_buf::open ( path pth, pipe_mode auto... args )
{
    // Check.
    if constexpr ( sizeof...(args) >= 1 )
        static_assert(detail::all_different<decltype(args)...>, "modes must be unique");

    // Find executable.
    let path_executable = boost::filesystem::path(pth.c_str());
    let find_executable = boost::process::v2::environment::find_executable(pth.c_str());

    // Open pipe.
    try
    {
        // Find_executable is always in higher priority than raw_path.
        process_handle = run_with_args(find_executable != "" ? find_executable otherwise path_executable,
                                       {}, tuple<decltype(args)...>(args...));
    }
    catch ( const boost::process::v2::system_error& e )
    {
        throw pipe_error("failed to open pipe {} (with path_executable = {}, find_executable = {}) [[caused by {}: {}]]",
                         pth,
                         boost::filesystem::is_regular_file(path_executable) ? path_executable otherwise "[[not exist]]",
                         find_executable != ""                               ? find_executable otherwise "[[not found]]",
                         typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
    }

    // Set put area.
    setp(stdin_buff.data(),
         stdin_buff.data() + stdin_buff.size());
}


// Auxiliary

auto pipe_buf::run_with_args ( boost::filesystem::path exe, std::vector<std::string> params, const auto& inputs, auto... outputs )
{
    if constexpr ( inputs.size == 0 )
        return std::make_unique<boost::process::v2::process>(io_context, exe, params, outputs...,
                                                             boost::process::v2::process_stdio(stdin_pipe, stdout_pipe, stderr_pipe));

    else if constexpr ( std::same_as<decltype(inputs.first),environment> )
    {
        let env = boost::process::v2::process_environment(inputs.first.value
                | std::views::transform([] (const auto& kv)
                                        {
                                            let k = std::string(kv.key());
                                            let v = std::string(kv.value()
                                                  | std::views::join_with(char_type(';'))
                                                  | std::ranges::to<string>());
                                            return std::pair(k, v);
                                        })
                | std::ranges::to<std::map<std::string,std::string>>());
        return run_with_args(exe, params, inputs.other, env, outputs...);
    }

    else if constexpr ( std::same_as<decltype(inputs.first),param> )
    {
        params = inputs.first.value
               | std::views::transform([] (const auto& prm) { return std::string(prm); })
               | std::ranges::to<std::vector<std::string>>();
        return run_with_args(exe, params, inputs.other, outputs...);
    }

    else if constexpr ( std::same_as<decltype(inputs.first),start_directory> )
    {
        let startdir = boost::process::v2::process_start_dir(inputs.first.value.c_str());
        return run_with_args(exe, params, inputs.other, startdir, outputs...);
    }

    else
        return run_with_args(exe, params, inputs.other, outputs...);
}





/// Class pipe_buf::mode_base

template < class type >
constexpr pipe_buf::mode_base<type>::mode_base ( type init )
    extends value ( std::move(init) )
{

}

template < array_type type >
constexpr pipe_buf::mode_base<type>::mode_base ( type::value_type init )
    extends value ( {std::move(init)} )
{

}

template < array_type type >
constexpr pipe_buf::mode_base<type>::mode_base ( type::value_type init, std::convertible_to<typename type::value_type> auto... args )
    extends value ( {std::forward<decltype(init)>(init), std::forward<decltype(args)>(args)...} )
{

}

template < array_type type >
constexpr pipe_buf::mode_base<type>::mode_base ( type init )
    extends value ( std::move(init) )
{

}

template < map_type type >
constexpr pipe_buf::mode_base<type>::mode_base ( type::key_type k, type::value_type::value_type v )
    extends value ( { { std::move(k), {std::move(v)} } } )
{

}

template < map_type type >
constexpr pipe_buf::mode_base<type>::mode_base ( type::key_type k, type::value_type v )
    extends value ( { { std::move(k), std::move(v) } } )
{

}

template < map_type type >
constexpr pipe_buf::mode_base<type>::mode_base ( pair<typename type::key_type,typename type::value_type::value_type> kv )
    extends value ( { { std::move(kv.key()), {std::move(kv.value())} } } )
{

}

template < map_type type >
constexpr pipe_buf::mode_base<type>::mode_base ( pair<typename type::key_type,typename type::value_type> kv )
    extends value ( { { std::move(kv.key()), std::move(kv.value()) } } )
{

}

template < map_type type >
constexpr pipe_buf::mode_base<type>::mode_base ( map<typename type::key_type,typename type::value_type::value_type> m )
    extends value ( m | std::views::transform([] (const auto& kv) { return pair<typename type::key_type,typename type::value_type>(kv.key(), {kv.value()}); })
                      | std::ranges::to<map<typename type::key_type,typename type::value_type>>() )
{

}

template < map_type type >
constexpr pipe_buf::mode_base<type>::mode_base ( map<typename type::key_type,typename type::value_type> m )
    extends value ( std::move(m) )
{

}





/// Class pipe_buf::tuple

template < class type, class... types >
constexpr pipe_buf::tuple<type,types...>::tuple ( type arg1, types... args )
    extends first ( std::forward<decltype(arg1)>(arg1) ),
            other ( std::forward<decltype(args)>(args)... )
{

}