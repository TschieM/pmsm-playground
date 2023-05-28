add_subdirectory(board)
add_subdirectory(peripherial)
add_subdirectory(uc)

add_executable(playground main.cc)

target_include_directories(playground
PUBLIC
    peripherial
    board
    uc
)

target_link_libraries(playground board peripherial uc)