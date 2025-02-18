#pragma once

string detail::encode_base64 ( const string& inputs )
{
    constexpr static const string_view chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    let outputs = string((inputs.size() + 2) / 3 * 4);

    int val  = 0;
    int valb = -6;
    for ( uint8_t ch in inputs )
    {
        val   = (val << 8) + ch;
        valb += 8;

        while (valb >= 0)
        {
            outputs.push(chars[((val >> valb) & 0x3F) + 1]);
            valb -= 6;
        }
    }

    if ( valb > -6 )
        outputs.push(chars[(((val << 8) >> (valb + 8)) & 0x3F) + 1]);

    while ( outputs.size() % 4 != 0 )
        outputs.push('=');

    return outputs;
}

