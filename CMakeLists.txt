cmake_minimum_required(VERSION 3.10)
project(ft_ssl_md5)

#Setup binary compilation
add_executable(ft_ssl
		srcs/ft_ssl.c
		srcs/t_queue.c
		srcs/t_list.c
		srcs/opt_md5.c
		srcs/opt_sha256.c
		srcs/display.c
		srcs/utility.c srcs/md5.c srcs/process_md5.c srcs/process_sha256.c)
target_include_directories(ft_ssl PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_compile_options(ft_ssl PRIVATE -Wall -Wextra -Werror -std=gnu11 -march=native -flto)