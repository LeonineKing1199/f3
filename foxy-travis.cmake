set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_COMPILER "g++-7")
add_compile_definitions("BOOST_ASIO_NO_DEPRECATED")
include("/vcpkg/scripts/buildsystems/vcpkg.cmake")
