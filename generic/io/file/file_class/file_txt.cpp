#pragma once

file_txt& file_txt::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);
    let stream = file_stream(path(self), file_stream::read_only(true));

    // Read data.
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

file_txt& file_txt::save ( )
{
    // Save file.
    file_interface::save();
    let stream = file_stream(path(self), file_stream::write_only(true), file_stream::erase(true));

    // Write data.
    self | std::views::reverse
         | std::views::drop_while([] (const auto& line) { return line.empty(); })
         | std::views::reverse
         | std::views::join_with('\n')
         | std::ranges::to<views::binary_ostream<char>>(std::ref(stream));

    return self;
}




