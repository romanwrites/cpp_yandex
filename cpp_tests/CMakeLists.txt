cmake_minimum_required(VERSION 3.17)
project(CPP_Yandex_tests)

set(CMAKE_CXX_STANDARD 11)

add_executable(sortVector
        sortVector.cpp)

add_executable(static
        protectedStaticMember.cpp)

add_executable(main
        main.cpp)

add_executable(palindrome
        palindrome.cpp)