//
// Copyright (c) 2018-2018 Christian Mazakas (christian dot mazakas at gmail dot
// com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/LeonineKing1199/foxy
//

#ifndef FOXY_URI_HPP_
#define FOXY_URI_HPP_

#include <boost/spirit/home/x3.hpp>
#include <boost/utility/string_view.hpp>

namespace foxy
{
namespace uri
{
namespace parser
{
namespace x3 = boost::spirit::x3;

using sub_delims_type = x3::rule<class sub_delims>;
BOOST_SPIRIT_DECLARE(sub_delims_type);

using gen_delims_type = x3::rule<class gen_delims>;
BOOST_SPIRIT_DECLARE(gen_delims_type);

using reserved_type = x3::rule<class reserved>;
BOOST_SPIRIT_DECLARE(reserved_type);

using unreserved_type = x3::rule<class unreserved>;
BOOST_SPIRIT_DECLARE(unreserved_type);

} // namespace parser

auto
sub_delims() -> parser::sub_delims_type;

auto
gen_delims() -> parser::gen_delims_type;

auto
reserved() -> parser::reserved_type;

auto
unreserved() -> parser::unreserved_type;

} // namespace uri
} // namespace foxy

#include <foxy/detail/uri_def.hpp>

#endif // FOXY_URI_HPP_