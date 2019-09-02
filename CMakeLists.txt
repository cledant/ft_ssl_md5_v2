cmake_minimum_required(VERSION 3.10)
project(ft_ssl_md5)

#Setup binary compilation
add_executable(ft_ssl
		packages/binary/private/ft_ssl.c
		packages/binary/private/debug.c
		packages/container/private/t_queue.c
		packages/container/private/t_list.c
		packages/md5/private/md5.c
		packages/args_parsing/private/opt_md5.c
		packages/args_parsing/private/opt_sha256.c
		packages/args_parsing/private/display.c
		packages/args_parsing/private/utility.c
		packages/args_processing/private/process_md5.c
		packages/args_processing/private/process_sha256.c
		packages/container/private/t_string.c
		packages/md5/private/md5_utility.c
		packages/container/private/t_byte_array.c
		packages/md5/private/md5_compute.c)
target_include_directories(ft_ssl PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/packages/shared_types/public
		${CMAKE_CURRENT_SOURCE_DIR}/packages/binary/private
		${CMAKE_CURRENT_SOURCE_DIR}/packages/args_parsing/public
		${CMAKE_CURRENT_SOURCE_DIR}/packages/args_parsing/private
		${CMAKE_CURRENT_SOURCE_DIR}/packages/args_processing/private
		${CMAKE_CURRENT_SOURCE_DIR}/packages/args_processing/public
		${CMAKE_CURRENT_SOURCE_DIR}/packages/container/public
		${CMAKE_CURRENT_SOURCE_DIR}/packages/container/private
		${CMAKE_CURRENT_SOURCE_DIR}/packages/md5/public
		${CMAKE_CURRENT_SOURCE_DIR}/packages/md5/private)
target_compile_options(ft_ssl PRIVATE -Wall -Wextra -Werror -std=gnu11 -march=native -flto)