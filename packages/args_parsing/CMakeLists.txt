cmake_minimum_required(VERSION 3.1)
project(args_parsing)

add_library(args_parsing STATIC
		private/opt_md5.c
		private/opt_sha256.c
		private/display.c
		private/utility.c)
target_include_directories(args_parsing
		PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/public
		PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/private)
add_dependencies(args_parsing container shared_types)
target_link_libraries(args_parsing container shared_types)
target_compile_options(args_parsing PRIVATE -Wall -Wextra -Werror -std=gnu11 -march=native -flto)