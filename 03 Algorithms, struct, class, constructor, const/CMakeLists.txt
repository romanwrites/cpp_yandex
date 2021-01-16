cmake_minimum_required(VERSION 3.17)
project(CPP_Yandex_week1)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-3")


set(CMAKE_CXX_STANDARD 11)

add_executable(01_SortAbs
        01_SortAbs.cpp)

add_executable(02_SortCaseInsensitively
        02_SortCaseInsensitively.cpp)

add_executable(03_SortedStrings
        03_SortedStrings.cpp)

add_executable(04_Names1
        04_Names1.cpp)

add_executable(05_Names2
        05_Names2.cpp)

add_executable(06_ReversibleString
        06_ReversibleString.cpp)
