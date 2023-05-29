# Add source files for the library
set(SOURCES pwm.cc qep.cc adc.cc)

# Generate the static library
add_library(uc STATIC ${SOURCES})