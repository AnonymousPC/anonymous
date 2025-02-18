#pragma once

string detail::encode_base64 ( const string& inputs )
{
    constexpr static const char* chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    let outputs = string((inputs.size() + 2) / 3 * 4);

    int c  = 0;
    int b = -6;
    for ( uint8_t ch in inputs )
    {
        c  = (c << 8) + ch;
        b += 8;

        while (b >= 0)
        {
            outputs.push(chars[((c >> b) & 0x3F)]);
            b -= 6;
        }
    }

    if ( b > -6 )
        outputs.push(chars[(((c << 8) >> (b + 8)) & 0x3F)]);

    while ( outputs.size() % 4 != 0 )
        outputs.push('=');

    return outputs;
}

