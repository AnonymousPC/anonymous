#pragma once

/// Class pipe_command

// Core

pipe_command::pipe_command ( const char* command, pipe_mode auto... args )
{
    execute(command, std::forward<decltype(args)>(args)...);
}

pipe_command::pipe_command ( const string& command, pipe_mode auto... args )
{
    execute(command, std::forward<decltype(args)>(args)...);
}

// Interface (special)

pipe_command& pipe_command::execute ( const string& command, pipe_mode auto... args )
{
    // Terminal.
    #ifdef _WIN32
        string terminal = "cmd";
    #elifdef __linux__
        string terminal = "bash";
    #elidef __MACH__
        string terminal = "zsh";
    #else
        string terminal = "terminal";
    #endif

    // Execute command.
    pipe_interface::open(terminal);
    let stream = pipe_stream(path(self), std::forward<decltype(args)>(args)...);

    // Input command.
    stream << command << std::endl
           << "exit"  << std::endl;

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