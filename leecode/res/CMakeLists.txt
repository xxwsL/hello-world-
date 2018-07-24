
include_directories(../inc)

# set(res_src
#     pailndrome_number_t.cpp
# )

aux_source_directory(. res_lib_src)
add_library(res_lib ${res_lib_src})