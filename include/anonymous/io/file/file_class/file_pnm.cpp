file_pnm::file_pnm ( path pth )
{
    open(pth);
}

file_pnm& file_pnm::open ( path pth )
{
    // Open file.
    file_interface::open(pth);

    // Read data.
    detail::read_from_boost_gil(self, self.operator path(), boost::gil::pnm_tag(), depth());

    return self;
}

file_pnm& file_pnm::save ( )
{
    // Save file.
    file_interface::save();

    // Write data.
    detail::write_to_boost_gil(self, self.operator path(), boost::gil::pnm_tag(), depth());

    return self;
}

file_pnm& file_pnm::close ( )
{
    // Close file.
    file_interface::close();

    // Clear data.
    matrix<color>::clear();

    return self;
}

int& file_pnm::depth ( )
{
    return image_depth;
}

const int& file_pnm::depth ( ) const
{
    return image_depth;
}
