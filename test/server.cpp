#pragma once

std::execution::sender auto receive_request ( int p )
{
    let stream = http_stream();
    stream.listen("https://0.0.0.0:{}"s.format(p));
    stream.peek();
    return std::execution::just(std::move(stream));
}

std::execution::sender auto send_response ( http_stream& stream )
{
    try
    {
        // if ( stream.request_method() == "GET" )
        // { 
        //     stream.response_header()["Content-Type"] = "text/html; charset=UTF-8";
        //     let reader = file_stream("test/{}"s.format(stream.request_path() == "" ? "index.html" otherwise stream.request_path()));
        //     views::binary_istream<char>(reader) | std::ranges::to<views::binary_ostream<char>>(std::ref(stream));
        //     stream << std::flush;
        // }

        // else if ( stream.request_method() == "POST" )
        // {
        //     let reader = file_txt("test/message");
        //     reader.push("self, {YYYY-MM-DD hh:mm:ss}, {}"s.format(now(), views::binary_istream<char>(stream) | std::ranges::to<string>()));
        //     reader.save();
        //     stream << std::flush;
        // }

        // else
        {
            stream.response_status_code() = 502;
            stream.response_reason() = "Bad Gateway";
            stream << "YOUR REQUEST IS BAD" << std::flush;
        }

        return std::execution::just(std::move(stream));
    }
    catch ( const file_error& e )
    {
        stream << "bad request: {}"s.format(e.what()) << std::flush;
        return std::execution::just(std::move(stream));
    }
}

std::execution::sender auto handle_error ( std::exception_ptr ptr )
{
    try
    {
        std::rethrow_exception(ptr);
    }
    catch ( const std::exception& e )
    {
        print("error: {}"s.format(e.what()));
    }
    
    return std::execution::just();
}


