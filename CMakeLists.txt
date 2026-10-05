cmake_minimum_required(VERSION 3.20)
project(sitema-estoque-c
    LANGUAGES C
    VERSION 1.0.3
    DESCRIPTION "Projeto de sistema de estoque em C")

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PostgreSQL REQUIRED)

add_executable(${PROJECT_NAME}
    src/main.c
    src/postgres-storage.c
    src/product.c
    src/terminal-ui.c
    src/utils.c
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE PostgreSQL::PostgreSQL)

if(UNIX)
    set_property(TARGET PostgreSQL::PostgreSQL APPEND PROPERTY INTERFACE_LINK_LIBRARIES m)
endif()
