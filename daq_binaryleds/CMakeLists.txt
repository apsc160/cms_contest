include_directories(managers)
set(SOURCES managers/grader.c)
include(../common/GenerateTaskTargets.cmake)

add_executable(daq_binary_leds_input input/generate.c)