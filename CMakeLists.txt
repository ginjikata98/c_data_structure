cmake_minimum_required(VERSION 3.23)
project(main C)

file(GLOB SOURCE_FILES src/*.c src/*.h)

set(CMAKE_C_STANDARD 99)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        /usr/local/include
)

target_link_directories(
        ${PROJECT_NAME} PUBLIC
        /usr/local/lib
)

target_link_libraries(
        ${PROJECT_NAME}
        pthread
)