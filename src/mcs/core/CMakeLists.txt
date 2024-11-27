file(GLOB_RECURSE core_files "**.cpp")
add_library(core_lib SHARED ${core_files})
target_include_directories(core_lib PUBLIC "../../../include/")
target_compile_definitions(core_lib PUBLIC _BUILD_MCS_LIBRARIES)