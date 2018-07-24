cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0)

include(CTest)
enable_testing()

#inc_dir path init
include_directories(inc)

#now dir srcs get 
aux_source_directory(. dir_srcs)

#create exe bin 
add_executable(main ${dir_srcs})

#other src files dir
add_subdirectory(res)

#link lib
target_link_libraries(main res_lib)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
