file(GLOB test_files "main.cpp")
add_executable(mcs_test ${test_files})
target_include_directories(mcs_test PUBLIC "../../include")
target_link_libraries(mcs_test core_lib logger_lib networking_lib buffer_lib)

add_executable(mcs_test_client "test_client.cpp")
target_include_directories(mcs_test_client PUBLIC "../../include" "../../vendor/asio/asio/include")
target_link_libraries(mcs_test_client core_lib logger_lib networking_lib buffer_lib)
