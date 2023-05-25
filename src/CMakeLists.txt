add_executable(pmsm_sim
    main.cc 
    motor/pmsm.cc
    board/inverter.cc 
    uc/pwm.cc
)

target_include_directories(pmsm_sim
    motor
    board
    uc
)

target_link_libraries(pmsm_sim yaml-cpp)