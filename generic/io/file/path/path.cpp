#pragma once

path::path ( std::filesystem::path pth )
    extends string ( pth.generic_string() )
{

}

path::operator std::filesystem::path ( ) const
{
    return std::filesystem::path(self.c_str());
}

path path::absolute_path ( ) const
{
    try
    {
        return std::filesystem::absolute ( std::filesystem::path(self) );
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot transform {} into absolute_path", self).from(e);
    }
}

path path::relative_path ( ) const
{
    try
    {
        return std::filesystem::relative ( std::filesystem::path(self) );
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot transform {} into relative_path", self).from(e);
    }
}

path path::parent_path ( ) const
{
    try
    {
        let p = std::filesystem::path(self).parent_path();
        return not p.empty() ? p otherwise ".";
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot get parent_path from {}", self).from(e);
    }
}

path path::child_path ( path p ) const
{
    try
    {
        return std::filesystem::path(self) / std::filesystem::path(p);
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot get child_path from {} to {}", self, p).from(e);
    }
}

path path::root_path ( ) const
{
    try
    {
        return std::filesystem::path(self).root_path();
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot get root_path from {}", self).from(e);
    }
}

const array<path> path::dir ( ) const
{
    try
    {
        return std::filesystem::directory_iterator(std::filesystem::path(self))
             | std::views::transform([] (const auto& entry) { return path(entry.path()); })
             | std::ranges::to<array<path>>();
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot iterator {} with dir", self).from(e);
    }
}

const array<path> path::ls ( ) const
{
    try
    {
        return std::filesystem::directory_iterator(std::filesystem::path(self))
             | std::views::transform([] (const auto& entry) { return path(entry.path()); })
             | std::ranges::to<array<path>>();
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot iterator {} with ls", self).from(e);
    }
}

const array<path> path::tree ( ) const
{
    try
    {
        return std::filesystem::recursive_directory_iterator(std::filesystem::path(self))
             | std::views::transform([] (const auto& entry) { return path(entry.path()); })
             | std::ranges::to<array<path>>();
    }
    catch ( const std::filesystem::filesystem_error& e )
    {
        throw file_error("cannot iterator {} with tree", self).from(e);
    }
}

bool operator == ( const path& p1, const path& p2 )
{
    if ( ( is_file(p1) or is_directory(p1) ) and ( is_file(p2) or is_directory(p2) ) )
        return std::filesystem::equivalent(std::filesystem::path(p1), std::filesystem::path(p2));

    else
        return static_cast<const string&>(p1) == static_cast<const string&>(p2);
}
