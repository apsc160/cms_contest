cmake_minimum_required(VERSION 3.2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

project(DAQ_contest)

include(CTest)
add_executable(runtest test/runtest.c)

include_directories(include)

set(CMAKE_BUILD_TYPE Debug)

# generate output files and the redirect command for redirecting inputs/outputs
set(OUTPUT_FILES)
set(STATEMENT_PDFS)

add_subdirectory(intro_addition)
add_subdirectory(intro_search)
add_subdirectory(intro_fileio)
add_subdirectory(intro_functions)
add_subdirectory(intro_magic)
add_subdirectory(intro_regression)
add_subdirectory(intro_base7)
add_subdirectory(daq_framework)
add_subdirectory(daq_indicator)
add_subdirectory(daq_toggle)
add_subdirectory(daq_binaryleds)
add_subdirectory(daq_writenumber)
add_subdirectory(daq_writenegative)
add_subdirectory(daq_rotateleds)
add_subdirectory(daq_timing)
add_subdirectory(daq_traffic)
add_subdirectory(daq_clock)
add_subdirectory(daq_slider)
add_subdirectory(daq_temperature)
add_subdirectory(daq_digitizer)
add_subdirectory(strings_safestrings)
add_subdirectory(strings_vigenere)
add_subdirectory(strings_palindrome)
add_subdirectory(strings_translate)

add_custom_target(output_files DEPENDS ${OUTPUT_FILES})
add_custom_target(statement_pdfs DEPENDS ${STATEMENT_PDFS})
