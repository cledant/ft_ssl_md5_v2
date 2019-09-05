cmake_minimum_required(VERSION 3.1)
project(shared_types)

add_library(shared_types INTERFACE)
target_include_directories(shared_types
		INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/public)