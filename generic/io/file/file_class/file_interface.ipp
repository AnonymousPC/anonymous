#pragma once

template < class type >
file_interface<type>::file_interface ( file_interface&& init )
    extends file_path ( std::exchange ( init.file_path, ""    ) ),
            file_open ( std::exchange ( init.file_open, false ) )
{

}

template < class type >
file_interface<type>& file_interface<type>::operator = ( file_interface&& right )
{
    file_path = std::exchange ( right.file_path, ""    );
    file_open = std::exchange ( right.file_open, false );
    return self;
}

template < class type >
file_interface<type>::file_interface ( const char* pth )
{
    static_cast<type&>(self).open(pth);
}

template < class type >
file_interface<type>::file_interface ( const path& pth )
{
    static_cast<type&>(self).open(pth);
}

template < class type >
type& file_interface<type>::open ( const path& pth )
{
    if ( file_open )
        throw file_error("cannot open file {}: file_interface has already opened {}", pth, file_path);

    if ( not is_file(pth) )
        throw file_error("cannot open file {}: file does not exist", pth);

    file_path = pth;
    file_open = true;

    return static_cast<type&>(self);
}

template < class type >
type& file_interface<type>::save ( )
{
    if ( not file_open )
        throw file_error("cannot save file {}: file_interface has not been opened", file_path);

    if ( not is_file(file_path) )
        throw file_error("cannot save file {}: file does not exist", file_path);

    return static_cast<type&>(self);
}

template < class type >
type& file_interface<type>::save_as ( const path& pth )
{
    if ( is_file(pth) )
        throw file_error("cannot save_as file {}: file already exists", pth);

    let tmp_path    = create_file(pth);
    let tmp_open    = true;
    let backup_path = file_path;
    let backup_open = file_open;

    try
    {
        std::swap ( file_path, tmp_path );
        std::swap ( file_open, tmp_open );
        static_cast<type&>(self).save();
        std::swap ( file_path, tmp_path );
        std::swap ( file_open, tmp_open );
    }
    catch ( ... )
    {
        try { remove_file(pth); } catch (...) { }
        file_path = backup_path;
        file_open = backup_open;
        throw;
    }

    return static_cast<type&>(self);
}

template < class type >
type& file_interface<type>::close ( )
{
    if ( not file_open )
        throw file_error("cannot close file: file_interface has not been opened");

    file_path = "";
    file_open = false;

    return static_cast<type&>(self);
}

template < class type >
bool file_interface<type>::is_open ( ) const
{
    return file_open;
}

template < class type >
file_interface<type>::operator path ( ) const
{
    return file_path;
}