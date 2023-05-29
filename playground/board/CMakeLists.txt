# Add source files for the library
set(SOURCES inverter.cc current_meas.cc)

# Generate the static library
add_library(board STATIC ${SOURCES})