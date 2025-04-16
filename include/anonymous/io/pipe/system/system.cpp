#pragma once

void wait_process ( int process_id )
{
    try
    {
        boost::process::v2::process(boost::asio::system_executor(), process_id).wait();
    }
    catch ( const boost::system::system_error& e )
    {
        throw pipe_error("failed to wait process (with process_id = {})", process_id).from(detail::system_error(e));
    }
}

void suspend_process ( int process_id )
{
    try
    {
        boost::process::v2::process(boost::asio::system_executor(), process_id).suspend();
    }
    catch ( const boost::system::system_error& e )
    {
        throw pipe_error("failed to suspend process (with process_id = {})", process_id).from(detail::system_error(e));
    }
}

void resume_process ( int process_id )
{
    try
    {
        boost::process::v2::process(boost::asio::system_executor(), process_id).resume();
    }
    catch ( const boost::system::system_error& e )
    {
        throw pipe_error("failed to resume process (with process_id = {})", process_id).from(detail::system_error(e));
    }
}

void interrupt_process ( int process_id )
{
    try
    {
        boost::process::v2::process(boost::asio::system_executor(), process_id).interrupt();
    }
    catch ( const boost::system::system_error& e )
    {
        throw pipe_error("failed to interrupt process (with process_id = {})", process_id).from(detail::system_error(e));
    }
}

int exit_process ( int process_id )
{
    try
    {
        auto handle = boost::process::v2::process(boost::asio::system_executor(), process_id);
        handle.request_exit();
        return handle.exit_code();
    }
    catch ( const boost::system::system_error& e )
    {
        throw pipe_error("failed to exit process (with process_id = {})", process_id).from(detail::system_error(e));
    }
}

int terminate_process ( int process_id )
{
    try
    {
        auto handle = boost::process::v2::process(boost::asio::system_executor(), process_id);
        handle.terminate();
        return handle.exit_code();
    }
    catch ( const boost::system::system_error& e )
    {
        throw pipe_error("failed to terminate process (with process_id = {})", process_id).from(detail::system_error(e));
    }
}