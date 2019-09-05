cmake_minimum_required(VERSION 3.1)
project(sha256)

add_library(sha256 STATIC
		private/sha256.c
		private/sha256_utility.c
		private/sha256_compute.c)
target_include_directories(sha256
		PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/public
		PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/private)
add_dependencies(sha256 container)
target_link_libraries(sha256 container)
target_compile_options(sha256 PRIVATE -Wall -Wextra -Werror -std=gnu11 -march=native -flto)