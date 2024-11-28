#pragma once

/// Class pipe_process

// Core

pipe_process::pipe_process ( const char* pth, pipe_mode auto... args )
{
    open(pth, std::forward<decltype(args)>(args)...);
}

pipe_process::pipe_process ( const path& pth, pipe_mode auto... args )
{
    open(pth, std::forward<decltype(args)>(args)...);
}

// Interface (override)

pipe_process& pipe_process::open ( const path& pth, pipe_mode auto... args )
{
    // Open process.
    pipe_interface::open(pth);
    let stream = pipe_stream(path(self), std::forward<decltype(args)>(args)...);

    // Read output.
    static_cast<vector<string>&>(self)
        = views::binary_istream<char>(stream)
        | std::views::lazy_split('\n')
        | std::views::transform ([] (const auto& stream_line)
            {
                let line = stream_line
                         | std::ranges::to<string>();
                return line.ends_with('\r') ? line.pop() otherwise line;
            })
        | std::ranges::to<vector<string>>();

    return self;
}