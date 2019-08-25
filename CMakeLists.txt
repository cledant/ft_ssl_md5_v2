cmake_minimum_required(VERSION 3.10)
project(ft_ssl_md5)

#Setup binary compilation
add_executable(ft_ssl
		srcs/ft_ssl.c srcs/ft_ssl.c)
target_include_directories(ft_ssl PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_compile_options(ft_ssl PRIVATE -Wall -Wextra -Werror -std=gnu11 -march=native -flto)