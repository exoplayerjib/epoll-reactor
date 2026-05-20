cmake_minimum_required(VERSION 3.15)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()
project(EpollReactor CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

add_library(reactor_lib 
    src/actor_thread_pool.cpp
    src/connection_handler.cpp
    src/executor.cpp
    src/reactor.cpp
)

target_include_directories(reactor_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(server_example examples/main.cpp)
target_link_libraries(server_example PRIVATE reactor_lib)


enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
add_executable(reactor_tests 
    tests/executor_test.cpp
    tests/actor_thread_pool_test.cpp
    tests/connection_handler_test.cpp
    tests/reactor_tests.cpp
)
target_link_libraries(reactor_tests PRIVATE reactor_lib gtest_main)
include(GoogleTest)
gtest_discover_tests(reactor_tests)