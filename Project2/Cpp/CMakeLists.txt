cmake_minimum_required(VERSION 3.10)

project(pro2)

aux_source_directory(./src DIR_SRCS)

include_directories(includes)

add_executable(pro2 ${DIR_SRCS})