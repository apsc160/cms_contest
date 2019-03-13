# grading manager
include_directories(managers)
set(SOURCES managers/grader.c)

# replace time
# include_directories(../common/src)
# set(SOURCES attachments/DAQlibTerminalTiming.c ../common/src/timing.c)

# attachment
# set(SOURCES attachments/DAQlibTerminalTiming.c)

include(../common/GenerateTaskTargets.cmake)