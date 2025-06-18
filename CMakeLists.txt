cmake_minimum_required(VERSION 3.31)
project(Raylib C)

set(CMAKE_C_STANDARD 11)

include(FetchContent)

function(include_dependency libName gitUrl gitTag)
    FetchContent_Declare(${libName}
        GIT_REPOSITORY ${gitUrl}
            GIT_TAG ${gitTag}
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(${libName})
endfunction()

set(LIB1 raylib)
find_package(${LIB1} QUIET)
if (NOT ${LIB1}_FOUND)
    include_dependency(${LIB1} http://github.com/raysan5/raylib.git 5.0)
endif()


# 1.PongClone
add_executable(PongClone 01.PongClone/main.c)
target_link_libraries(PongClone PRIVATE raylib)

# 2.BreakoutGame
add_executable(BreakoutGame 02.BreakoutGame/main.c
        02.BreakoutGame/paddle.h
        02.BreakoutGame/paddle.c
        02.BreakoutGame/config.h
        02.BreakoutGame/brick.h
        02.BreakoutGame/brick.c
        02.BreakoutGame/ball.h
        02.BreakoutGame/ball.c)
target_link_libraries(BreakoutGame PRIVATE raylib)


# ===============================
# target_include_directories(Raylib PRIVATE ${raylib_INCLUDE_DIRS})
# target_link_libraries(Raylib PRIVATE ${LIB1})
