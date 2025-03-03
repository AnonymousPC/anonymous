#pragma once

file_stream::file_stream ( )
{
    exceptions(std::ios::badbit);
}

file_stream::~file_stream ( )
{
    exceptions(std::ios::iostate());
}




