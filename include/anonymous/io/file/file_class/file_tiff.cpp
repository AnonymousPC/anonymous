file_tiff::file_tiff ( path pth )
{
    open(pth);
}

file_tiff& file_tiff::open ( path pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.
    detail::read_from_boost_gil(self, self.operator path(), boost::gil::tiff_concept(), depth());

    return self;
}

file_tiff& file_tiff::save ( )
{
    // Save file.
    file_interface::save();

    // Write data.
    detail::write_to_boost_gil(self, self.operator path(), boost::gil::tiff_concept(), depth());

    return self;
}

file_tiff& file_tiff::close ( )
{
    // Close file.
    file_interface::close();

    // Clear data.
    matrix<color>::clear();

    return self;
}

int& file_tiff::depth ( )
{
    return image_depth;
}

const int& file_tiff::depth ( ) const
{
    return image_depth;
}
