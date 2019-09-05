cmake_minimum_required(VERSION 3.1)
project(container)

add_library(container STATIC
		private/t_string.c
		private/t_queue.c
		private/t_list.c
		private/t_byte_array.c
		private/endianness.c
		private/rotate_data.c)
target_include_directories(container
		PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/public
		PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/private)
target_compile_options(container PRIVATE -Wall -Wextra -Werror -std=gnu11 -march=native -flto)