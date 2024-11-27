file(GLOB_RECURSE buffer_files "**.cpp")
add_library(buffer_lib SHARED ${buffer_files})

target_include_directories(buffer_lib PUBLIC "../../../include/")
target_compile_definitions(buffer_lib PUBLIC _BUILD_MCS_LIBRARIES)