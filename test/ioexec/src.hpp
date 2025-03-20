#define ASIO_TO_EXEC_USE_BOOST
#include <boost/asio.hpp>

/*
  Copyright (c) 2024 SamGaaWaa

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#pragma once

#if !defined(ASIO_TO_EXEC_USE_BOOST)
#include "asio/async_result.hpp"
#include "asio/error_code.hpp"
#include "asio/io_context.hpp"
#include "asio/cancellation_signal.hpp"
#include "asio/associated_executor.hpp"
#include "asio/post.hpp"
#else
#include "boost/asio/async_result.hpp"
#include "boost/asio/io_context.hpp"
#include "boost/asio/cancellation_signal.hpp"
#include "boost/asio/associated_executor.hpp"
#include "boost/asio/post.hpp"
#endif

#include "stdexec/execution.hpp"

#include <atomic>
#include <cassert>
#include <concepts>
#include <cstring>
#include <memory>
#include <memory_resource>
#include <optional>
#include <thread>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>

namespace asio2exec
{

    namespace __ex = stdexec;
#if !defined(ASIO_TO_EXEC_USE_BOOST)
    namespace __io = asio;
#else
    namespace __io = boost::asio;
#endif

    namespace __detail
    {
        struct scheduler_t;
    }

    #include "asio_context.hpp"
    #include "use_sender.hpp"

    namespace __detail
    {
        #include "buffer.hpp"
        #include "scheduler.hpp"
        #include "op_base.hpp"
        #include "use_sender_handler.hpp"
        #include "any.hpp"
        #include "initializer.hpp"
        #include "tuple_helper.hpp"
        #include "sender.hpp"
    } // __detail

    inline __detail::scheduler_t asio_context::get_scheduler() noexcept { return __detail::scheduler_t{_ctx}; }

    template <class... Args>
    using sender = __detail::__sender<Args...>;

    using scheduler = __detail::scheduler_t;

    static_assert(__ex::scheduler<scheduler>);

} // asio2exec

#if !defined(ASIO_TO_EXEC_USE_BOOST)
namespace asio
{
#else
namespace boost::asio
{
#endif
    #include "async_result.hpp"
} // asio