cmake_minimum_required(VERSION 3.1)
project(args_processing)

add_library(args_processing STATIC
		private/process_md5.c
		private/process_sha256.c
		private/utility.c)
target_include_directories(args_processing
		PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/public
		PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/private)
add_dependencies(args_processing container sha256 md5 shared_types)
target_link_libraries(args_processing container sha256 md5 shared_types)
target_compile_options(args_processing PRIVATE -Wall -Wextra -Werror -std=gnu11 -march=native -flto)