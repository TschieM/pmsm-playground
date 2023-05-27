add_executable(playground
    main.cc 
    peripherial/pmsm.cc
    board/inverter.cc 
    uc/pwm.cc
)

target_include_directories(playground
PUBLIC
    peripherial
    board
    uc
)

target_link_libraries(playground yaml-cpp Eigen3::Eigen)