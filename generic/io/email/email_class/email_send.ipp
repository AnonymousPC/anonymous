#pragma once

email_send::email_send ( email_mode auto... args )
{
    static_assert ( ( same_as<decltype(args),server  > or ... ) and
                    ( same_as<decltype(args),username> or ... ) and
                    ( same_as<decltype(args),password> or ... ) and
                    ( same_as<decltype(args),from    > or ... ) and
                    ( same_as<decltype(args),to      > or ... ) and
                    ( same_as<decltype(args),title   > or ... ) and
                    ( same_as<decltype(args),data    > or ... ) and
                    detail::all_different<decltype(args)...>,
                    "you must provide all email params: server, username, password, from, to, title, data" );
            
    let email_server   = index_value_of<detail::index_of_unique_same_type<server,  decltype(args)...>>(args...).value;
    let email_username = index_value_of<detail::index_of_unique_same_type<username,decltype(args)...>>(args...).value;
    let email_password = index_value_of<detail::index_of_unique_same_type<password,decltype(args)...>>(args...).value;
    let email_from     = index_value_of<detail::index_of_unique_same_type<from,    decltype(args)...>>(args...).value;
    let email_to       = index_value_of<detail::index_of_unique_same_type<to,      decltype(args)...>>(args...).value;
    let email_title    = index_value_of<detail::index_of_unique_same_type<title,   decltype(args)...>>(args...).value;
    let email_data     = index_value_of<detail::index_of_unique_same_type<data,    decltype(args)...>>(args...).value;

    let stream = ssl_stream(url(email_server));
    stream << "EHLO localhost\r\n"
           << "AUTH LOGIN\r\n"
           << "{}\r\n"s            .format(detail::encode_base64(email_username))
           << "{}\r\n"s            .format(detail::encode_base64(email_password))
           << "MAIL FROM:<{}>\r\n"s.format(email_from)
           << "RCPT TO:<{}>\r\n"s  .format(email_to)

           << "DATA\r\n"

           << "From: {}\r\n"s      .format(email_from)
           << "To: {}\r\n"s        .format(email_to)
           << "Subject: {}\r\n"s   .format(email_title)
           << "\r\n"
           << "{}\r\n"s            .format(email_data)
           << ".\r\n"

           << "QUIT\r\n"
           << std::flush;
           
    let line_count = 1;
    let response = views::binary_istream<char>(stream)
                 | std::views::lazy_split('\n')
                 | std::views::transform([&] (const auto& line)
                     {
                         let str = line
                                 | std::ranges::to<string>();
                         if ( str.size() >= 4 and str[1,3].is_digit() and str[4,4].is_space() )
                             line_count++;
                         return not str.ends_with('\r') ? str otherwise string(str[1,-2]);
                     })
                 | std::views::take_while([&] (const auto&) { return line_count <= 9; })
                 | std::ranges::to<vector<string>>();
    if ( response.exist([] (const auto& line) { return line.begins_with('4') or line.begins_with('5'); }) )
        throw network_error("send email failed (with server_response = [[see_below]])\n"
                            "{}", response | std::views::join_with('\n') | std::ranges::to<string>());
    
    stream.close();

}