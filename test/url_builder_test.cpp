#include <foxy/url_builder.hpp>
#include <foxy/iterator.hpp>
#include <foxy/uri.hpp>

#include <boost/utility/string_view.hpp>

#include <string>

#include <catch2/catch.hpp>

TEST_CASE("Our URL builder class...")
{
  SECTION("should not encode pct-encoded and the sub-delims")
  {
    auto const host = boost::u32string_view(U"%20%13%24!$'()*+,;=");

    auto out = std::string(256, '\0');

    auto const end          = foxy::detail::encode_host(host, out.begin());
    auto const encoded_host = boost::string_view(out.data(), end - out.begin());

    CHECK(encoded_host == "%20%13%24!$'()*+,;=");
  }

  SECTION("should pct-encode misc. whitespace chars")
  {
    auto const host = boost::u32string_view(U"hello world!\n");
    auto       out  = std::string(256, '\0');

    auto const encoded_host =
      boost::string_view(out.data(), foxy::detail::encode_host(host, out.begin()) - out.begin());

    CHECK(encoded_host == "hello%20world!%0a");
  }

  SECTION("should pct-encode a Polish hostname")
  {
    auto const host = boost::u32string_view(U"www.\u017C\u00F3\u0142\u0107.pl");
    auto       out  = std::string(256, '\0');

    auto const encoded_host =
      boost::string_view(out.data(), foxy::detail::encode_host(host, out.begin()) - out.begin());

    CHECK(encoded_host == "www.%c5%bc%c3%b3%c5%82%c4%87.pl");
  }

  SECTION("should not pct-encode a valid IPv4 address")
  {
    auto const host = boost::u32string_view(U"127.0.0.1");
    auto       out  = std::string(256, '\0');

    auto const encoded_host =
      boost::string_view(out.data(), foxy::detail::encode_host(host, out.begin()) - out.begin());

    CHECK(encoded_host == "127.0.0.1");
  }

  SECTION("should not pct-encode a valid IP-literal [IPv6 edition]")
  {
    auto const host = boost::u32string_view(U"[::]");
    auto       out  = std::string(256, '\0');

    auto const encoded_host =
      boost::string_view(out.data(), foxy::detail::encode_host(host, out.begin()) - out.begin());

    CHECK(encoded_host == "[::]");
  }

  SECTION("should pct-encode seemingly random entries into the ASCII set")
  {
    auto const host = boost::u32string_view(U"\"#/<>?@[\\]^`{|}");
    auto       out  = std::string(256, '\0');

    auto const encoded_host =
      boost::string_view(out.data(), foxy::detail::encode_host(host, out.begin()) - out.begin());

    CHECK(encoded_host == "%22%23%2f%3c%3e%3f%40%5b%5c%5d%5e%60%7b%7c%7d");
  }
}
