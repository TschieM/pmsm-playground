add_executable(pmsm_sim
    main.cc 
    pmsm.cc
    inverter.cc 
    motor_phase.cc
)

target_link_libraries(pmsm_sim yaml-cpp)