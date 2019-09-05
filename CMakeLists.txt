cmake_minimum_required(VERSION 3.1)
project(ft_ssl_md5)

add_subdirectory(packages/container)
add_subdirectory(packages/md5)
add_subdirectory(packages/sha256)
add_subdirectory(packages/args_processing)
add_subdirectory(packages/args_parsing)
add_subdirectory(packages/shared_types)

add_executable(ft_ssl
		packages/binary/private/ft_ssl.c)
target_include_directories(ft_ssl PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/packages/shared_types/public
		${CMAKE_CURRENT_SOURCE_DIR}/packages/binary/private)
add_dependencies(ft_ssl args_parsing args_processing container md5 sha256)
target_link_libraries(ft_ssl args_parsing args_processing container md5 sha256 bsd)
target_compile_options(ft_ssl PRIVATE -Wall -Wextra -Werror -std=gnu11 -march=native -flto)