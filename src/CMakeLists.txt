add_executable(pmsm_sim
    main.cc 
    pmsm_sim.cc
)

target_link_libraries(pmsm_sim yaml-cpp)