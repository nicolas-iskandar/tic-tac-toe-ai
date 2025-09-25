include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(tictactoe_tests test_tictactoe.cpp ../src/tictactoe.cpp)
target_include_directories(tictactoe_tests PRIVATE ../include)
target_link_libraries(tictactoe_tests gtest_main)

include (GoogleTest)
gtest_discover_tests(tictactoe_tests)
