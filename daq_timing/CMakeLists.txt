# grading manager
include_directories(managers)
set(SOURCES managers/grader.c)

# replace time
# include_directories(../common/src)
# set(SOURCES attachments/DAQlibTerminalTiming.c ../common/src/timing.c)

# attachment - real time
# set(SOURCES attachments/DAQlibTerminalTiming.c)

add_executable(daq_timing_input_generator input/generator.c)

include(../common/GenerateTaskTargets.cmake)