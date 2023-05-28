# Add source files for the library
set(SOURCES encoder.cc pmsm.cc)

# Generate the static library
add_library(peripherial STATIC ${SOURCES})

target_link_libraries(peripherial yaml-cpp Eigen3::Eigen)