//
// Copyright (c) 2018-2018 Christian Mazakas (christian dot mazakas at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/LeonineKing1199/f3
//

#ifndef FOXY_LOG_HPP_
#define FOXY_LOG_HPP_

#include <boost/system/error_code.hpp>
#include <boost/utility/string_view.hpp>
#include <iostream>

namespace foxy
{

auto log_error(boost::system::error_code const ec, boost::string_view const what) -> void;

} // foxy

#endif // FOXY_LOG_HPP_
