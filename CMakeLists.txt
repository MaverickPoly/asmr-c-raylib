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
        02.BreakoutGame/ball.c
        08.FallingBlocks/config.h
)
target_link_libraries(BreakoutGame PRIVATE raylib)


# 3.FlappyCube
add_executable(FlappyCube 03.FlappyCube/main.c
        03.FlappyCube/config.h
        03.FlappyCube/cube.h
        03.FlappyCube/cube.c
)
target_link_libraries(FlappyCube PRIVATE raylib)

# 4.SnakeGame
add_executable(SnakeGame 04.SnakeGame/main.c
        04.SnakeGame/config.h
        04.SnakeGame/snake.c
        04.SnakeGame/snake.h
)
target_link_libraries(SnakeGame PRIVATE raylib)

# 5.DinoRunner
add_executable(DinoRunner 05.DinoRunner/main.c
        05.DinoRunner/dino.c
        05.DinoRunner/dino.h
        05.DinoRunner/config.h
        05.DinoRunner/cactus.c
        05.DinoRunner/cactus.h
)
target_link_libraries(DinoRunner PRIVATE raylib)

# 7.CameraMovement
add_executable(CameraMovement 07.CameraMovement/main.c)
target_link_libraries(CameraMovement PRIVATE raylib)

# 8.FallingBlocks
add_executable(FallingBlocks 08.FallingBlocks/main.c
        08.FallingBlocks/config.h)
target_link_libraries(FallingBlocks PRIVATE raylib)

# 9.MouseCircle
add_executable(MouseCircle 09.MouseCircle/main.c)
target_link_libraries(MouseCircle PRIVATE raylib)

# 10.TicTacToe
add_executable(TicTacToe 10.TicTacToe/main.c)
target_link_libraries(TicTacToe PRIVATE raylib)


# ===============================
# target_include_directories(Raylib PRIVATE ${raylib_INCLUDE_DIRS})
# target_link_libraries(Raylib PRIVATE ${LIB1})
