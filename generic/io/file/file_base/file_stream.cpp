#pragma once

file_stream::file_stream ( )
{
    // Set exception cases.
    exceptions(std::ios::badbit);
}

file_stream::~file_stream ( )
{
    // Reset exception cases.
    exceptions(std::ios::iostate());
}




