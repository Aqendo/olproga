cmake_minimum_required(VERSION 3.12)
project(untitled)
add_definitions(-DLOCAL)
add_definitions(-DSEREGA)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(untitled main.cpp bits/stdc++.h)
add_executable(slow slow.cpp
        #        printer.h
        #        helper.h
        bits/stdc++.h)
# add_executable(testgen testgen.cpp bits/stdc++.h)
#target_precompile_headers(untitled PRIVATE bits/stdc++.h)
#target_precompile_headers(slow PRIVATE bits/stdc++.h)
# target_precompile_headers(testgen PRIVATE bits/stdc++.h)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftrapv -ggdb -O0 -D_FORTIFY_SOURCE=2")
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC")
