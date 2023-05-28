# Add source files for the library
set(SOURCES pwm.cc)

# Generate the static library
add_library(uc STATIC ${SOURCES})