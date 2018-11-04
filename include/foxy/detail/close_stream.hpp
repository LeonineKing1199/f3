//
// Copyright (c) 2018-2018 Christian Mazakas (christian dot mazakas at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/LeonineKing1199/foxy
//

#include <foxy/type_traits.hpp>

namespace foxy
{
namespace detail
{

template <
  class Stream,
  std::enable_if_t<
    is_closable_stream_throw<Stream>::value &&
    !is_closable_stream_nothrow<Stream>::value, int> = 0
>
auto
close(Stream& stream)
{
  try {
    stream.close();
  } catch(...) {}
}

template <
  class Stream,
  std::enable_if_t<is_closable_stream_nothrow<Stream>::value, int> = 0
>
auto
close(Stream& stream)
{
  auto ec = boost::system::error_code();
  stream.close(ec);
}

} // detail
} // foxy
