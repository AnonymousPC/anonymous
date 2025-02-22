#pragma once

matrix<typename sql_stream::value_type> sql_stream::execute_result ( const boost::mysql::results& results )
{
    return matrix<value_type>(results.rows().size(), results.rows().num_columns(), [&] (int i, int j) { return make_result_arg(results.rows()[i-1][j-1]); });
}

sql_stream::value_type sql_stream::make_result_arg ( const boost::mysql::field_view& field )
{
    switch ( field.kind() )
    {
        case boost::mysql::field_kind::int64:    return field.get_int64();
        case boost::mysql::field_kind::uint64:   return field.get_uint64();
        case boost::mysql::field_kind::float_:   return field.get_float();
        case boost::mysql::field_kind::double_:  return field.get_double();
        case boost::mysql::field_kind::string:   return field.get_string() | std::ranges::to<string>();
        case boost::mysql::field_kind::blob:     return field.get_blob()   | std::ranges::to<vector<char>>();
        case boost::mysql::field_kind::date:     return time_point(field.get_date    ().get_time_point());
        case boost::mysql::field_kind::datetime: return time_point(field.get_datetime().get_time_point());
        case boost::mysql::field_kind::time:     return duration  (field.get_time    ());
        case boost::mysql::field_kind::null:     return nullptr;
        default: throw logic_error("internel error");
    }
}