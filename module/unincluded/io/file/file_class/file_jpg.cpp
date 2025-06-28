file_jpg::file_jpg ( path pth )
{
    open(pth);
}

file_jpg& file_jpg::open ( path pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.
    detail::read_from_boost_gil(self, self.operator path(), boost::gil::jpeg_concept(), depth());

    return self;
}

file_jpg& file_jpg::save ( )
{
    // Save file.
    file_interface::save();

    // Write data.
    detail::write_to_boost_gil(self, self.operator path(), boost::gil::jpeg_concept(), depth());

    return self;
}

file_jpg& file_jpg::close ( )
{
    // Close file.
    file_interface::close();

    // Clear data.
    matrix<color>::clear();

    return self;
}

int& file_jpg::depth ( )
{
    return image_depth;
}

const int& file_jpg::depth ( ) const
{
    return image_depth;
}
