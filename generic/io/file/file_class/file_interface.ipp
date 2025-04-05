#pragma once

template < class type >
type& file_interface<type>::open ( path pth )
{
    if ( file_path != "" )
        throw file_error("cannot open file {}: file handler has already been opened", pth);
    if ( not is_file(pth) )
        throw file_error("cannot open file {}: file does not exist", pth);

    file_path = pth;
    return static_cast<type&>(self);
}

template < class type >
type& file_interface<type>::save ( )
{
    if ( file_path == "" )
        throw file_error("cannot save file {}: file handler has not been opened", file_path);
    if ( not is_file(file_path) )
        throw file_error("cannot save file {}: file does not exist", file_path);

    return static_cast<type&>(self);
}

template < class type >
type& file_interface<type>::close ( )
{
    if ( file_path == "" )
        throw file_error("cannot close file {}: file handler has not been opened", file_path);

    file_path = "";
    return static_cast<type&>(self);
}

template < class type >
type& file_interface<type>::save_as ( path pth )
{
    if ( is_file(pth) )
        throw file_error("cannot save_as file {}: file already exists", pth);

    let old_path = file_path;
    let new_path = create_file(pth);
    try
    {
        file_path = new_path;
        static_cast<type&>(self).save();
        file_path = old_path;
    }
    catch ( ... )
    {
        try { remove_file(pth); } catch (...) { }
        file_path = old_path;
        throw;
    }

    return static_cast<type&>(self);
}

template < class type >
bool file_interface<type>::is_open ( ) const
{
    return file_path != "";
}

template < class type >
file_interface<type>::operator path ( ) const
{
    return file_path;
}


