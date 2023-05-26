add_executable(pmsm_sim
    main.cc 
    motor/pmsm.cc
    board/inverter.cc 
    uc/pwm.cc
)

target_include_directories(pmsm_sim
PUBLIC
    motor
    board
    uc
)

target_link_libraries(pmsm_sim yaml-cpp Eigen3::Eigen)