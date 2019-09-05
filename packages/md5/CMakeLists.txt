cmake_minimum_required(VERSION 3.1)
project(md5)

add_library(md5 STATIC
		private/md5.c
		private/md5_utility.c
		private/md5_compute.c)
target_include_directories(md5
		PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/public
		PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/private)
add_dependencies(md5 container)
target_link_libraries(md5 container)
target_compile_options(md5 PRIVATE -Wall -Wextra -Werror -std=gnu11 -march=native -flto)