cmake_minimum_required(VERSION 3.28)
project(map)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,leak,undefined")
add_executable(main
        src/utility.hpp
        src/map.hpp
        src/exceptions.hpp
        main.cpp
)
add_executable(main2
        src/utility.hpp
        src/map.hpp
        src/exceptions.hpp
        main2.cpp
)
add_executable(code1
        src/utility.hpp
        src/map.hpp
        src/exceptions.hpp
        data/one/code.cpp
)
add_executable(code2
        src/utility.hpp
        src/map.hpp
        src/exceptions.hpp
        data/two/code.cpp
)
add_executable(code3
        src/utility.hpp
        src/map.hpp
        src/exceptions.hpp
        data/three/code.cpp
)
add_executable(code4
        src/utility.hpp
        src/map.hpp
        src/exceptions.hpp
        data/four/code.cpp
)
add_executable(code5
        src/utility.hpp
        src/map.hpp
        src/exceptions.hpp
        data/five/code.cpp
)
