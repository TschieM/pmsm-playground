# Add source files for the library
set(SOURCES inverter.cc)

# Generate the static library
add_library(board STATIC ${SOURCES})