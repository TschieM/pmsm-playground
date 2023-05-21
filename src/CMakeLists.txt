add_executable(pmsm_sim
    main.cc 
    hw_simulation/motor/pmsm.cc
    hw_simulation/board/inverter.cc 
    hw_simulation/motor/motor_phase.cc
    hw_simulation/uc/pwm.cc
)

target_include_directories(pmsm_sim
    hw_simulation/motor
    hw_simulation/board
    hw_simulation/uc
)

target_link_libraries(pmsm_sim yaml-cpp)