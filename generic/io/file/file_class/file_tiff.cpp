#pragma once

/// Class file_tiff

// Core

file_tiff::file_tiff ( const char* pth )
{
    open(pth);
}

file_tiff::file_tiff ( const path& pth )
{
    open(pth);
}

// Interface (override)

file_tiff& file_tiff::open ( const path& pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.
    aux::read_from_boost_gil(self, path(self), boost::gil::tiff_tag(), depth());

    return self;
}

file_tiff& file_tiff::save ( )
{
    // Save file.
    file_interface::save();

    // Write data.
    aux::write_to_boost_gil(self, path(self), boost::gil::tiff_tag(), depth());

    return self;
}


// Interface

int& file_tiff::depth ( )
{
    return image_depth;
}

const int& file_tiff::depth ( ) const
{
    return image_depth;
}
