file(GLOB_RECURSE logger_files "**.cpp")
add_library(logger_lib SHARED ${logger_files})

target_include_directories(logger_lib PUBLIC "../../../include/" "../../vendor/spdlog/include/")
target_compile_definitions(logger_lib PUBLIC _BUILD_MCS_LIBRARIES)
target_link_libraries(logger_lib PRIVATE spdlog)


