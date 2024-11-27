file(GLOB_RECURSE networking_files "**.cpp")
add_library(networking_lib SHARED ${networking_files})

target_include_directories(networking_lib PUBLIC "../../../include/" "../../../vendor/asio/include/")
target_compile_definitions(networking_lib PUBLIC _BUILD_MCS_LIBRARIES)