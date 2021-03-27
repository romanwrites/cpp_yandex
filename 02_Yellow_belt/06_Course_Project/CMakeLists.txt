cmake_minimum_required(VERSION 3.17)
project(CPP_Yandex_week1)

include_directories(.)

set(CMAKE_CXX_STANDARD 11)

add_executable(final
        condition_parser.cpp
        condition_parser_test.cpp
        database.cpp
        date.cpp
        main.cpp
        node.cpp
        token.cpp
        test_runner.cpp)
