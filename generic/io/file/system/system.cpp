#pragma once

/// File

bool is_file ( const path& p )
{
    return std::filesystem::is_regular_file(std::filesystem::path(p));
}

path create_file ( const path& p )
{
    if ( not is_directory(p.parent_path()) )
        throw file_error("cannot create file {}: parent_path does not exist", p);

    if ( is_file(p) )
        throw file_error("cannot create file {}: file already exists", p);

    if ( is_directory(p) )
        throw file_error("cannot create file {}: file's path is already taken by a directory", p);

    try
    {
        let stream = std::ofstream();
        stream.exceptions(std::ios::failbit);
        stream.open(std::filesystem::path(p), std::ios::binary);
    }
    catch ( const std::ios_base::failure& e )
    {
        throw file_error("cannot create file {} [[caused by {}: {}]]", p, typeid(e), e.what());
    }

    return p;
}

path try_create_file ( const path& p )
{
    try
    {
        return create_file(p);
    }
    catch ( const file_error& )
    {
        return p;
    }
}

path remove_file ( const path& p )
{
    if ( not is_file(p) )
        throw file_error("cannot remove file {}: file does not exist", p);

    try
    {
        std::filesystem::remove(std::filesystem::path(p));
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot remove file {} [[caused by {}: {}]]", p, typeid(e), e.what());
    }

    return p;
}

path try_remove_file ( const path& p )
{
    try
    {
        return remove_file(p);
    }
    catch ( const file_error& )
    {
        return p;
    }
}

path copy_file ( const path& p1, const path& p2 )
{
    if ( p1 == p2 )
        throw file_error("cannot copy file {} to {}: the source file is same as the the target file", p1, p2);

    if ( not is_file(p1) )
        throw file_error("cannot copy file {} to {}: the source file does not exist", p1, p2);

    if ( not is_directory(p2.parent_path()) )
        throw file_error("cannot copy file {} to {}: the target file's parent_path does not exist", p1, p2);

    if ( is_file(p2) )
        throw file_error("cannot copy file {} to {}: the target file already exists", p1, p2);

    if ( is_directory(p2) )
        throw file_error("cannot copy file {} to {}: the target file's path is already taken by a directory", p1, p2);

    try
    {
        std::filesystem::copy_file(std::filesystem::path(p1), std::filesystem::path(p2));
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot copy file {} to {} [[caused by {}: {}]]", p1, p2, typeid(e), e.what());
    }

    return p2;
}

path try_copy_file ( const path& p1, const path& p2 )
{
    try
    {
        return copy_file(p1, p2);
    }
    catch ( const file_error& e )
    {
        return p2;
    }
}

path move_file ( const path& p1, const path& p2 )
{
    if ( p1 == p2 )
        throw file_error("cannot move file {} to {}: the source file is same as the target file", p1, p2);

    if ( not is_file(p1) )
        throw file_error("cannot move file {} to {}: the source file does not exist", p1, p2);

    if ( not is_directory(p2.parent_path()) )
        throw file_error("cannot move file {} to {}: the target file's parent_path does not exist", p1, p2);

    if ( is_file(p2) )
        throw file_error("cannot move file {} to {}: the target file already exists", p1, p2);

    if ( is_directory(p2) )
        throw file_error("cannot move file {} to {}: thr target file's path is already taken by a directory", p1, p2);

    try
    {
        std::filesystem::rename(std::filesystem::path(p1), std::filesystem::path(p2));
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot move file {} to {} [[caused by {}: {}]]", p1, p2, typeid(e), e.what());
    }

    return p2;
}

path try_move_file ( const path& p1, const path& p2 )
{
    try
    {
        return move_file(p1, p2);
    }
    catch ( const file_error& e )
    {
        return p2;
    }
}

path rename_file ( const path& p1, const path& p2 )
{
    if ( p1 == p2 )
        throw file_error("cannot rename file {} to {}: the source file is same as the target file", p1, p2);

    if ( p1.parent_path() != p2.parent_path() )
        throw file_error("cannot rename file {} to {}: the source file is in different directory with the target file", p1, p2);

    if ( not is_file(p1) )
        throw file_error("cannot rename file {} to {}: the source file does not exist", p1, p2);

    if ( is_file(p2) )
        throw file_error("cannot rename file {} to {}: the target file already exists", p1, p2);

    if ( is_directory(p2) )
        throw file_error("cannot rename file {} to {}: the target file's path is already taken by a directory", p1, p2);

    try
    {
        std::filesystem::rename(std::filesystem::path(p1), std::filesystem::path(p2));
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot rename file {} to {} [[caused by {}: {}]]", p1, p2, typeid(e), e.what());
    }

    return p2;
}

path try_rename_file ( const path& p1, const path& p2 )
{
    try
    {
        return rename_file(p1, p2);
    }
    catch (const file_error& e )
    {
        return p2;
    }
}

intmax_t size_of_file ( const path& p )
{
    if ( not is_file(p) )
        throw file_error("cannot query size of file {}: file does not exist", p);

    try
    {
        return std::filesystem::file_size(std::filesystem::path(p));
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot query size of file {} [[caused by {}: {}]]", p, typeid(e), e.what());
    }

}



/// Directory

path current_directory ( )
{
    return std::filesystem::current_path();
}

bool is_directory ( const path& p )
{
    return std::filesystem::is_directory(std::filesystem::path(p));
}

path create_directory ( const path& p )
{
    if ( not is_directory(p.parent_path()) )
        throw file_error("cannot create directory {}: parent_path does not exist", p);

    if ( is_directory(p) )
        throw file_error("cannot create directory {}: directory already exists", p);

    if ( is_file(p) )
        throw file_error("cannot create directory {}: directory's path is already taken by a file", p);

    try
    {
        std::filesystem::create_directory(std::filesystem::path(p));
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot create directory {} [[caused by {}: {}]]", p, typeid(e), e.what());
    }

    return p;
}

path try_create_directory ( const path& p )
{
    try
    {
        return create_directory(p);
    }
    catch ( const file_error& )
    {
        return p;
    }
}

path remove_directory ( const path& p )
{
    if ( not is_directory(p) )
        throw file_error("cannot remove directory {}: directory does not exist", p);

    try
    {
        std::filesystem::remove_all(std::filesystem::path(p));
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot remove directory {} [[caused by {}: {}]]", p, typeid(e), e.what());
    }

    return p;
}

path try_remove_directory ( const path& p )
{
    try
    {
        return remove_directory(p);
    }
    catch ( const file_error& )
    {
        return p;
    }
}

path copy_directory ( const path& p1, const path& p2 )
{
    if ( p1 == p2 )
        throw file_error("cannot copy directory {} to {}: the source directory is same as the the target directory", p1, p2);

    if ( not is_directory(p1) )
        throw file_error("cannot copy directory {} to {}: the source directory does not exist", p1, p2);

    if ( not is_directory(p2.parent_path()) )
        throw file_error("cannot copy directory {} to {}: the target directory's parent_path does not exist", p1, p2);

    if ( is_directory(p2) )
        throw file_error("cannot copy direcory {} to {}: the target directory already exists", p1, p2);

    if ( is_file(p2) )
        throw file_error("cannot copy directory {} to {}: the target directory's path is already taken by a file", p1, p2);

    try
    {
        std::filesystem::copy(std::filesystem::path(p1), std::filesystem::path(p2), std::filesystem::copy_options::recursive);
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot copy directory {} to {} [[caused by {}: {}]]", p1, p2, typeid(e), e.what());
    }

    return p2;
}

path try_copy_directory ( const path& p1, const path& p2 )
{
    try
    {
        return copy_directory(p1, p2);
    }
    catch ( const file_error& )
    {
        return p2;
    }
}

path move_directory ( const path& p1, const path& p2 )
{
    if ( p1 == p2 )
        throw file_error("cannot move directory {} to {}: the source directory is same as the target directory", p1, p2);

    if ( not is_directory(p1) )
        throw file_error("cannot move directory {} to {}: the source directory does not exist", p1, p2);

    if ( not is_directory(p2.parent_path()) )
        throw file_error("cannot move directory {} to {}: the target directory's parent_path does not exist", p1, p2);

    if ( is_directory(p2) )
        throw file_error("cannot move directory {} to {}: the target directory already exists", p1, p2);

    if ( is_file(p2) )
        throw file_error("cannot move directory {} to {}: thr target directory's path is already taken by a file", p1, p2);

    try
    {
        std::filesystem::rename(std::filesystem::path(p1), std::filesystem::path(p2));
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot move directory {} to {} [[caused by {}: {}]]", p1, p2, typeid(e), e.what());
    }

    return p2;
}

path try_move_directory ( const path& p1, const path& p2 )
{
    try
    {
        return move_directory(p1, p2);
    }
    catch ( const file_error& )
    {
        return p2;
    }
}

path rename_directory ( const path& p1, const path& p2 )
{
    if ( p1 == p2 )
        throw file_error("cannot rename directory {} to {}: the source directory is same as the target directory", p1, p2);

    if ( p1.parent_path() != p2.parent_path() )
        throw file_error("cannot rename directory {} to {}: the source directory is in different directory with the target directory", p1, p2);

    if ( not is_directory(p1) )
        throw file_error("cannot rename directory {} to {}: the source directory does not exist", p1, p2);

    if ( is_directory(p2) )
        throw file_error("cannot rename directory {} to {}: the target directory already exists", p1, p2);

    if ( is_file(p2) )
        throw file_error("cannot rename directory {} to {}: the target directory's path is already taken by a file", p1, p2);

    try
    {
        std::filesystem::rename(std::filesystem::path(p1), std::filesystem::path(p2));
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot rename directory {} to {} [[caused by {}: {}]]", p1, p2, typeid(e), e.what());
    }

    return p2;
}

path try_rename_directory ( const path& p1, const path& p2 )
{
    try
    {
        return rename_directory(p1, p2);
    }
    catch ( const file_error& )
    {
        return p2;
    }
}

intmax_t size_of_directory ( const path& p )
{
    if ( not is_directory(p) )
        throw file_error("cannot query size of directory {}: directory does not exist", p);

    try
    {
        let pathes = std::filesystem::recursive_directory_iterator(std::filesystem::path(p));
        let files  = pathes | std::views::filter([] (const auto& pth) { return std::filesystem::is_regular_file(pth); });
        return std::accumulate ( files.begin(), files.end(), intmax_t(0), [] (const auto& a, const auto& b) { return a + std::filesystem::file_size(b); } );
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot query size of directory {} [[caused by {}: {}]]", p, typeid(e), e.what());
    }
}
