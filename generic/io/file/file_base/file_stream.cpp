#pragma once

/// Class file_stream

// Core

file_stream::file_stream ( )
{
    // Set exception cases.
    exceptions(std::ios::badbit);
}

file_stream::~file_stream ( )
{
    // Reset exception cases.
    exceptions(std::ios::iostate());
}

// Auxiliary

std::ios::openmode file_stream::make_std_openmode ( mode_type modes )
{
    #undef in

    // Initialize.
    let std_modes = std::ios::binary;

    // Common case.
    if ( modes.read_only )
        std_modes |= std::ios::in;
    if ( modes.write_only )
        std_modes |= std::ios::out;
    if ( modes.erase )
        std_modes |= std::ios::trunc;
    if ( modes.append )
        std_modes |= std::ios::app;

    // Special case.
    if ( not modes.read_only and not modes.write_only ) // Non explicit read-only or write-only means both read and write.
        std_modes |= ( std::ios::in | std::ios::out );
    if ( not modes.read_only and modes.write_only and not modes.erase and not modes.append ) // Write-only with non expicit modes means non-erase non-append.
        std_modes |= std::ios::in;

    return std_modes;

    #define in :
}



