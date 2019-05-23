//
// Copyright (c) 2018-2019 Christian Mazakas (christian dot mazakas at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/LeonineKing1199/foxy
//

#ifndef FOXY_PCT_ENCODE_HPP_
#define FOXY_PCT_ENCODE_HPP_

#include <foxy/iterator.hpp>

#include <boost/spirit/include/karma_generate.hpp>
#include <boost/spirit/include/karma_string.hpp>
#include <boost/spirit/include/karma_sequence.hpp>
#include <boost/spirit/include/karma_numeric.hpp>

#include <boost/utility/string_view.hpp>
#include <boost/locale/utf.hpp>

#include <cstdint>
#include <cstring>
#include <string>
#include <array>

namespace foxy
{
namespace uri
{
template <class OutputIterator>
auto
utf8_encode(boost::locale::utf::code_point const code_point, OutputIterator sink) -> OutputIterator
{
  return boost::locale::utf::utf_traits<char>::encode(code_point, sink);
}

// to_utf8_encoding takes the Boost.Locale type `utf::code_point` which is capable of holding any
// Unicode code point. We convert the number to an unsigned 32 bit integer which represents the 1-4
// byte UTF-8 binary encoding scheme seen here:
// https://en.wikipedia.org/wiki/UTF-8#Description
//
// UTF-8 encoding writes the representation of the code point's value to the binary templates
// described below:
//
// 7 bits =>  [U+0000,  U+007F]   => 0xxxxxxx
// 11 bits => [U+0080,  U+07FF]   => 110xxxxx 10xxxxxx
// 16 bits => [U+0800,  U+FFFF]   => 1110xxxx 10xxxxxx 10xxxxxx
// 21 bits => [U+10000, U+10FFFF] => 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
//
template <class InputIterator, class OutputIterator>
auto
utf8_encoding(InputIterator begin, InputIterator end, OutputIterator sink) -> OutputIterator
{
  for (auto curr = begin; curr != end; ++curr) {
    auto const code_point = *curr;

    sink = utf8_encode(code_point, sink);
  }

  return sink;
}

template <class Char, class OutputIterator, class Traits = std::char_traits<Char>>
auto
pct_encode(boost::basic_string_view<Char, Traits> const input, OutputIterator sink)
  -> OutputIterator
{
  namespace karma = boost::spirit::karma;
  namespace utf   = boost::locale::utf;

  auto const points = code_point_view<Char>(input);

  for (auto const code_point : points) {
    if (code_point == utf::illegal || code_point == utf::incomplete) { return sink; }

    // no need to encode the normal ascii set
    //
    if ((code_point > 32) && (code_point < 123)) { continue; }

    auto buffer = std::array<std::uint8_t, 4>{0xff, 0xff, 0xff, 0xff};

    auto const end = utf8_encode(code_point, buffer.begin());

    for (auto pos = buffer.begin(); pos < end; ++pos) {
      karma::generate(sink, karma::lit("%") << karma::hex, *pos);
    }
  }

  return sink;
}
} // namespace uri
} // namespace foxy

#endif // FOXY_PCT_ENCODE_HPP_