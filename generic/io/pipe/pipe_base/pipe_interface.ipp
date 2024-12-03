#pragma once

/// Class pipe_interface

// Core

template < class pipe_type >
pipe_interface<pipe_type>::pipe_interface ( pipe_interface&& init )
    extends pipe_path ( std::exchange ( init.pipe_path,  ""    ) ),
            pipe_open ( std::exchange ( init.pipe_open,  false ) )
{

}

template < class pipe_type >
pipe_interface<pipe_type>& pipe_interface<pipe_type>::operator = ( pipe_interface&& right )
{
    pipe_path = std::exchange ( right.pipe_path,  ""    );
    pipe_open = std::exchange ( right.pipe_open,  false );
    return self;
}


// Interface (override)

template < class pipe_type >
pipe_type& pipe_interface<pipe_type>::open ( const path& pth )
{
    if ( pipe_open )
        throw file_error("cannot open pipe {}: pipe_interface has already opened {}", pth, pipe_path);

    pipe_path = pth;
    pipe_open = true;

    return static_cast<pipe_type&>(self);
}

// Interface (non-override)

template < class pipe_type >
pipe_type& pipe_interface<pipe_type>::close ( )
{
    if ( not pipe_open )
        throw file_error("cannot close pipe: pipe_interface has not been opened");

    pipe_path = "";
    pipe_open = false;

    return static_cast<pipe_type&>(self);
}

// Conversion

template < class pipe_type >
pipe_interface<pipe_type>::operator path ( ) const
{
    return pipe_path;
}