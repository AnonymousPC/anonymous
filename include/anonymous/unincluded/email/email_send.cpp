struct email_send::server     extends public detail::io_mode<url>           { using detail::io_mode<url>          ::io_mode; struct email_mode_tag { }; };
struct email_send::username   extends public detail::io_mode<string>        { using detail::io_mode<string>       ::io_mode; struct email_mode_tag { }; };
struct email_send::password   extends public detail::io_mode<string>        { using detail::io_mode<string>       ::io_mode; struct email_mode_tag { }; };
struct email_send::from       extends public detail::io_mode<string>        { using detail::io_mode<string>       ::io_mode; struct email_mode_tag { }; };
struct email_send::to         extends public detail::io_mode<array<string>> { using detail::io_mode<array<string>>::io_mode; struct email_mode_tag { }; };
struct email_send::cc         extends public detail::io_mode<array<string>> { using detail::io_mode<array<string>>::io_mode; struct email_mode_tag { }; };
struct email_send::bcc        extends public detail::io_mode<array<string>> { using detail::io_mode<array<string>>::io_mode; struct email_mode_tag { }; };
struct email_send::title      extends public detail::io_mode<string>        { using detail::io_mode<string>       ::io_mode; struct email_mode_tag { }; };
struct email_send::data       extends public detail::io_mode<string>        { using detail::io_mode<string>       ::io_mode; struct email_mode_tag { }; };
struct email_send::attachment extends public detail::io_mode<array<string>> { using detail::io_mode<array<string>>::io_mode; struct email_mode_tag { }; };
// Must use array<string> instead of array<path>, because "utility/io_mode.hpp" instantiates "array<path>" and is included before "file/path.hpp". 

email_send::email_send ( email_mode auto... args )
{
    // Get params.
    static_assert ( ( same_as<decltype(args),server  > or ... ) and
                    ( same_as<decltype(args),username> or ... ) and
                    ( same_as<decltype(args),password> or ... ) and
                    "you must provide server, username and password" );
    static_assert ( ( same_as<decltype(args),to      > or ... ) or
                    ( same_as<decltype(args),cc      > or ... ) or
                    ( same_as<decltype(args),bcc     > or ... ),
                    "you must choose at least one receiver" );
    static_assert ( detail::all_different<decltype(args)...>,
                    "duplicated params" );
    auto email_server   = index_value_of<detail::find_same_type<server,  decltype(args)...>>(args...).value;
    auto email_username = index_value_of<detail::find_same_type<username,decltype(args)...>>(args...).value;
    auto email_password = index_value_of<detail::find_same_type<password,decltype(args)...>>(args...).value;
    auto email_from = [&] -> string
        {
            if constexpr ( ( same_as<from,decltype(args)> or ... ) ) 
                return index_value_of<detail::find_same_type<from,decltype(args)...>>(args...).value;
            else
                return email_username;
        } ();
    auto email_to = [&] -> array<string>
        {
            if constexpr ( ( same_as<to,decltype(args)> or ... ) ) 
                return index_value_of<detail::find_same_type<to,decltype(args)...>>(args...).value;
            else
                return {};
        } ();
    auto email_cc = [&] -> array<string>
        {
            if constexpr ( ( same_as<cc,decltype(args)> or ... ) ) 
                return index_value_of<detail::find_same_type<cc,decltype(args)...>>(args...).value;
            else
                return {};
        } ();
    auto email_bcc = [&] -> array<string>
        {
            if constexpr ( ( same_as<bcc,decltype(args)> or ... ) ) 
                return index_value_of<detail::find_same_type<bcc,decltype(args)...>>(args...).value;
            else
                return {};
        } ();
    auto email_title = [&] -> string
        {
            if constexpr ( ( same_as<title,decltype(args)> or ... ) ) 
                return index_value_of<detail::find_same_type<title,decltype(args)...>>(args...).value;
            else
                return "";
        } ();
    auto email_data = [&] -> string
        {
            if constexpr ( ( same_as<data,decltype(args)> or ... ) ) 
                return index_value_of<detail::find_same_type<data,decltype(args)...>>(args...).value;
            else
                return "";
        } ();
    auto email_attachment = [&] -> array<path>
        {
            if constexpr ( ( same_as<attachment,decltype(args)> or ... ) ) 
                return index_value_of<detail::find_same_type<attachment,decltype(args)...>>(args...).value | std::ranges::to<array<path>>();
            else
                return {};
        } ();

    // Check params.
    if ( email_to.empty() and email_cc.empty() and email_bcc.empty() )
        throw logic_error("send an email with no receivers (with to = {}, cc = {}, bcc = {})", email_to, email_cc, email_bcc);

    // Send email.
    auto stream = ssl_stream();
    stream.connect(email_server);

    stream << "ehlo localhost\r\n"
           << "auth login\r\n"
           << "{}\r\n"s                                             .format(email_username | views::encode_base64 | std::ranges::to<string>())
           << "{}\r\n"s                                             .format(email_password | views::encode_base64 | std::ranges::to<string>())
           << "mail from:<{}>\r\n"s                                 .format(email_from)
           <</*rcpt to:<{}>\r\n*/"{}"s                              .format(array<array<string>>{email_to, email_cc, email_bcc} | std::views::join | std::ranges::to<set<string>>() | std::views::transform([] (const auto& rcpt) { return "rcpt to:<{}>\r\n"s.format(rcpt); }) | std::views::join | std::ranges::to<string>())
           << "data\r\n"
           << "From: {}\r\n"s                                       .format(email_from)
           << "To: {}\r\n"s                                         .format(email_to.empty() ? "" : email_to | std::views::join_with(", "s) | std::ranges::to<string>())
           << "Cc: {}\r\n"s                                         .format(email_cc.empty() ? "" : email_cc | std::views::join_with(", "s) | std::ranges::to<string>())
           << "Subject: {}\r\n"s                                    .format(email_title)
           << "MIME-Version: 1.0\r\n"
           << "Content-Type: multipart/mixed; boundary=boundary\r\n"
           << "\r\n"

           << "--boundary\r\n"
           << "Content-Type: text/plain; charset={}\r\n"s           .format(std::text_encoding::literal().name())
           << "\r\n"
           << "{}\r\n"s                                             .format(email_data)
           << "\r\n";

    // Send attachment
    for ( const auto& atc in email_attachment )
    {
        stream << "--boundary\r\n"
               << "Content-Type: application/octet-stream; name=\"{}\"\r\n"s.format(atc)
               << "Content-Transfer-Encoding: base64\r\n"
               << "Content-Disposition: attachment; filename=\"{}\"\r\n"s   .format(atc)
               << "\r\n";
        auto attach_stream = file_stream(atc, file_stream::read_only(true));
        views::binary_istream<char>(attach_stream)
            | views::encode_base64
            | std::ranges::to<views::binary_ostream<char>>(std::ref(stream)); stream << "\r\n";
        stream << "\r\n";
    }

    // Send goodbye
    stream << "--boundary--\r\n";
    stream << ".\r\n"
           << "quit\r\n"
           << std::flush;

    // Check response.
    auto line_count = 1;
    auto response   = vector<string>();
    try
    {
        std::ranges::for_each(
            views::binary_istream<char>(stream)
                | std::views::take_while([&] (const auto&) { return line_count <= 9; })
                | std::views::lazy_split('\n'),
            [&] (const auto& line)
                {
                    auto str = line | std::ranges::to<string>();
                    if ( str.size() >= 4 and str[1,3].is_digit() and str[4,4].is_space() )
                        line_count++;
                    response.push(std::move(not str.ends_with('\r') ? str : str.pop()));
                }
        );
    }
    catch ( network_error& )
    {
        response.push("...");
    }

    if ( response.exist([] (const auto& line) { return line.begins_with('4') or line.begins_with('5'); }) )
        throw network_error("send email failed (with server_response = [[see_below]])\n"
                            "{}", response | std::views::join_with('\n') | std::ranges::to<string>());
    
    // Exit.
    try { stream.close(); } catch (...) { }
}