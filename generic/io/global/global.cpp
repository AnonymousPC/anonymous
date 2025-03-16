#pragma once

boost::asio::io_context   io_context  = boost::asio::io_context();
boost::asio::ssl::context ssl_context = boost::asio::ssl::context(boost::asio::ssl::context::sslv23);
boost::asio::ssl::context tls_context = boost::asio::ssl::context(boost::asio::ssl::context::tls);

detail::io_initializer_t::io_initializer_t ( )
{
    try
    {
        ssl_context.set_default_verify_paths();
        ssl_context.set_options          (boost::asio::ssl::context::default_workarounds
                                         |boost::asio::ssl::context::single_dh_use);
        ssl_context.use_certificate_chain(boost::asio::buffer(cert_file.data(), cert_file.size()));
        ssl_context.use_private_key      (boost::asio::buffer(key_file .data(), key_file .size()), boost::asio::ssl::context::pem);
        ssl_context.use_tmp_dh           (boost::asio::buffer(dh_file  .data(), dh_file  .size()));
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("failed to create ssl_context").from(detail::system_error(e));
    }
    
    try
    {
        tls_context.set_default_verify_paths();
        tls_context.set_options          (boost::asio::ssl::context::default_workarounds
                                         |boost::asio::ssl::context::no_sslv2
                                         |boost::asio::ssl::context::no_sslv3
                                         |boost::asio::ssl::context::single_dh_use);
        tls_context.use_certificate_chain(boost::asio::buffer(cert_file.data(), cert_file.size()));
        tls_context.use_private_key      (boost::asio::buffer(key_file .data(), key_file .size()), boost::asio::ssl::context::pem);
        tls_context.use_tmp_dh           (boost::asio::buffer(dh_file  .data(), dh_file  .size()));
    }
    catch ( const boost::system::system_error& e )
    {
        throw network_error("failed to create tls_context").from(detail::system_error(e));
    }
}

string detail::io_initializer_t::cert_file = 
    "-----BEGIN CERTIFICATE-----\n"
    "MIIEITCCAwmgAwIBAgIUIKYZ4nO8Ttv7lWs+CEM78MGQRcUwDQYJKoZIhvcNAQEL\n"
    "BQAwgbgxCzAJBgNVBAYTAkNOMT8wPQYDVQQIDDZBbm9ueW1vdXMbWzE7MkQbWzE7\n"
    "MkQbWzE7MkQbWzE7MkQbWzE7MkQbWzE7MkQbW0QbW0QbW0QxEjAQBgNVBAcMCUFu\n"
    "b255bW91czESMBAGA1UECgwJQW5vbnltb3VzMRIwEAYDVQQLDAlBbm9ueW1vdXMx\n"
    "EjAQBgNVBAMMCUFub255bW91czEYMBYGCSqGSIb3DQEJARYJQW5vbnltb3VzMB4X\n"
    "DTI1MDIyMTE3MDY1NFoXDTI2MDIyMTE3MDY1NFowgbgxCzAJBgNVBAYTAkNOMT8w\n"
    "PQYDVQQIDDZBbm9ueW1vdXMbWzE7MkQbWzE7MkQbWzE7MkQbWzE7MkQbWzE7MkQb\n"
    "WzE7MkQbW0QbW0QbW0QxEjAQBgNVBAcMCUFub255bW91czESMBAGA1UECgwJQW5v\n"
    "bnltb3VzMRIwEAYDVQQLDAlBbm9ueW1vdXMxEjAQBgNVBAMMCUFub255bW91czEY\n"
    "MBYGCSqGSIb3DQEJARYJQW5vbnltb3VzMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8A\n"
    "MIIBCgKCAQEA1P5+WfZs9QflfQyxiBUrwd3Q3tnnPwjtv7Yp4eDHf9dfwt9bXl46\n"
    "gABwiSE6GftOK52Z4GeMcz/000uPoTJvHnbAezsj5lni7Ab1wvVQjn4iT+c+QlI9\n"
    "OpFT92b01V02MzqlUi4HLTyoD9y/VYYx5SrWiRstl65HbbthHFP5wiT/XCzEFPjI\n"
    "0FHHkKqXjDfco4iwY6HY9XegreNPw2CJDVxiSy0QGPm//6U8yu+0GmR0ITWiZov5\n"
    "NUIcffAgOuDc7LzBWDqK3cRLMCoUdGKtD1Leu657pqLHs/gB24iabO2CwVeNCGi/\n"
    "pTB25aRrvwUkhZyj3enk+rBOp9wh/MoJ7wIDAQABoyEwHzAdBgNVHQ4EFgQUFmK+\n"
    "aYPSzruyOhX0fAGiE0j54pQwDQYJKoZIhvcNAQELBQADggEBAG4ao00R3h2bhGtS\n"
    "x1KIk0TWRN1ZEloCVihishx5gM0XnioHAy7BYo7vqF9/wzKeumKfDFLUBMCgEenH\n"
    "+22WZwrJeXE21HxZgscnRFdjeY5GgO4iVK51lwUnnSdJKLvHOXxoShu0qqxFY/7E\n"
    "2bqhfK3N4/QuK11X8hc+D+Bg/r3Pw/Jk2op5cJkOPMM3BWjKwuRlkLjV/xBnCvWW\n"
    "OgXG3By0mK/2qV1frt4OXe15+BIr7Fs8NAihgIEpiZLng+sbRywZx96ke0UYpvk6\n"
    "5sP6LqKB/88dj3vt9u0Dmn+5I0lSABhMIjd2Ck7KR5pq/VoU6wtgsKoRB5mVhNnB\n"
    "U43HE0k=\n"
    "-----END CERTIFICATE-----\n";

string detail::io_initializer_t::key_file =
    "-----BEGIN PRIVATE KEY-----\n"
    "MIIEvAIBADANBgkqhkiG9w0BAQEFAASCBKYwggSiAgEAAoIBAQDU/n5Z9mz1B+V9\n"
    "DLGIFSvB3dDe2ec/CO2/tinh4Md/11/C31teXjqAAHCJIToZ+04rnZngZ4xzP/TT\n"
    "S4+hMm8edsB7OyPmWeLsBvXC9VCOfiJP5z5CUj06kVP3ZvTVXTYzOqVSLgctPKgP\n"
    "3L9VhjHlKtaJGy2Xrkdtu2EcU/nCJP9cLMQU+MjQUceQqpeMN9yjiLBjodj1d6Ct\n"
    "40/DYIkNXGJLLRAY+b//pTzK77QaZHQhNaJmi/k1Qhx98CA64NzsvMFYOordxEsw\n"
    "KhR0Yq0PUt67rnumosez+AHbiJps7YLBV40IaL+lMHblpGu/BSSFnKPd6eT6sE6n\n"
    "3CH8ygnvAgMBAAECggEAA3z7GI6t5rto39a0rgJbjTK/rqg9HpRCWuvpHRWZBTgQ\n"
    "dB9DuBsGwT1NZ0/sfpI8WJmEDh+tnKuU+MR/7ZQz+EWnASQNG/Yn5O6rDE5t/pw3\n"
    "ndbIxCRKc9DMFVaragOIFWgZK595jZ00ywG1/njfc1ENL2fX1zT+K+CWoA4+BMoE\n"
    "eRFyDUbpRdQrYQsebuYeZfCxamPuKl/rbx368sTKyl2Q7UoR6HsIB+xtSECWzhjZ\n"
    "zX0ms1hyokau37kT97AwJuXQ4XWvA2Est5i8xEt9f+/3Of2A2C0FgxKJwTSnj1kY\n"
    "CwYWtOlEKvhimCTCFtF4H8NW8ClIcTNjQ7cnE48z5QKBgQDxi9RAkRbbFM1gCdFm\n"
    "1/v9+cVXPreAp8ZKLYV5uJEp+S0TVq2XHm/joB6UyFV7kpDoXzOU/KidRL4Np9vP\n"
    "754kBsTm3tlcsWOOEvxGFGC2O4yjeCOnM5JW8iiUNabN6+hcDq9AcSmO4pk9QpBi\n"
    "/p0n5JQU2PcCtbLjZTbpFSnOYwKBgQDhvUir5AN54Bh5RPJb/ZbXOzBWSTTqcQVF\n"
    "FLh09EjPW9h3XtRWYbYgdOIgRnefSXDfIkKxZQjh+u9azWinyjvRzYcis+uM5akb\n"
    "AEH4NAL3m5aJaZQfrr/NBEv5q7Ma/82B4OwN9NLKJDoRp58U5dDH7tij7+H44n/M\n"
    "7qK+YDmWBQKBgGRO/UYS+rrgWKmZaiybZTqDj0A7+1iiU+ZaISP7Uc1sfRua01v+\n"
    "d9i/lfOTfmxi4Wqenn0wr5UgBw0EuHQRvkqXxQ1bXkjwIbfOipVPwRnsgOsh6Sx2\n"
    "bj9NMSzbWvoJDeWs83p/hBKiZ6DZE70In5sBgb1mnK2zZyan0bXZ5BKhAoGAUua0\n"
    "vYurSyLlWgPcDbR/pONzyPxxlneTO990Ll9YLe7I/G2zBVY1EI5cTQYUAEd0UD3A\n"
    "yG0WagdBx9MP0C8Q8OfN7QyuQLxG8keR8pkHTe+xxR0k7M28WoptbG+GAzBWRJBZ\n"
    "oHZ8wwey27D3VzFfD03D+dCq6EAmNxicY9Xq0BECgYA5cofn6cixiZZ8ly/af5Si\n"
    "F/yozl5taackwqa91iwUkmLL/ngq1IEiUdi6HT5ozL2mYGTxp4Ve/xUq9ivEirbR\n"
    "DN6z6ST6KOSScYAT9knTPOjuAF1R9f3T5jbizj58bljfjRci3RAYWFfl6vE6WT7x\n"
    "UOcWZw9imAi2The4lMb/aw==\n"
    "-----END PRIVATE KEY-----\n";

string detail::io_initializer_t::dh_file =
    "-----BEGIN DH PARAMETERS-----\n"
    "MIIBDAKCAQEAiXrenfnh9U6LpKnpeHgvMKfcGIcH5J6+ae/R72eKHOoQ6Gt1Dn0/\n"
    "ugGzYkLHF83jISBLeOP5NK3YQPpFpf54ApxVacWTLCBYkRF/be72H2HOKlMQKL23\n"
    "p6mOCcKGsLuRPS/1LFoJb9pggHFZUqToGOvOK5aqogx4MhzuM0112K4nOG3ulu0b\n"
    "eituJO2BWZ0L6vM/SWubHKfI7J8WSVt3D3xFLhlBINEdEY8J0woQ2tvDUk+xRrdq\n"
    "WTWN5lmI5xWS22d5TaHkP+/OsabXOoD5xTdBLJcGX1cE9XVOsSX2y8C9C6KTW6e8\n"
    "Rnk9frvt1++YMNIs4GZZsNpMoNhmnhFcVwIBAgICAOE=\n"
    "-----END DH PARAMETERS-----\n";