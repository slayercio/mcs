file(GLOB_RECURSE protocol_files "**.cpp")
add_library(protocol_lib SHARED ${protocol_files})

target_include_directories(protocol_lib PUBLIC "../../../include/")
target_compile_definitions(protocol_lib PUBLIC _BUILD_MCS_LIBRARIES)