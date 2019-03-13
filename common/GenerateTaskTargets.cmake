function (GenerateTaskTargets EXERCISE)

	# include all files in solution dir
	file(GLOB solution_files "${CMAKE_CURRENT_SOURCE_DIR}/solution/*.c")

	# append explicit source files
	list(APPEND solution_files ${SOURCES})

	# search solution dir for headers
	include_directories("${CMAKE_CURRENT_SOURCE_DIR}/solution/")

	add_executable(${EXERCISE} ${solution_files})

	# link math library
	target_link_libraries(${EXERCISE} m)

	# collect all inputs
	file(GLOB input_files "${CMAKE_CURRENT_SOURCE_DIR}/input/*.txt")
	set(${EXERCISE}_OUTPUTS "")
	
	# generate output targets
	foreach(input ${input_files})
		# get test index
		string(REGEX REPLACE ".*/input/input([0-9]+).txt" "\\1" IDX "${input}")

		# output files
		string(REPLACE "input" "output" output ${input})
        	get_filename_component(output_dir "${output}" DIRECTORY)
		add_custom_target( 
			${EXERCISE}_OUTPUT_${IDX} 
                	COMMAND ${CMAKE_COMMAND} -E make_directory "${output_dir}"
			COMMAND ${EXERCISE} < "${input}" > "${output}"
			DEPENDS ${EXERCISE}
   			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		)
		list(APPEND ${EXERCISE}_OUTPUTS ${EXERCISE}_OUTPUT_${IDX})

		# tests
		ADD_TEST (
			NAME ${EXERCISE}_TEST_${IDX}
			COMMAND runtest $<TARGET_FILE:${EXERCISE}> "${input}" test.txt "${output}"
		)
		set_tests_properties(${EXERCISE}_TEST_${IDX} PROPERTIES TIMEOUT 10) 
	endforeach()

	# build statement pdf
	add_custom_target( 
		${EXERCISE}_STATEMENT 
		COMMAND pandoc statement.md -V geometry:margin=1in --highlight-style ../../common/prism.theme -o statement.pdf
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/statement
	)

	# add output file targets
	set(OUTPUT_FILES ${OUTPUT_FILES} ${${EXERCISE}_OUTPUTS} PARENT_SCOPE)
	set(STATEMENT_PDFS ${STATEMENT_PDFS} ${EXERCISE}_STATEMENT PARENT_SCOPE)

endfunction(GenerateTaskTargets)

# generate targets
get_filename_component(EXERCISE ${CMAKE_CURRENT_SOURCE_DIR} NAME)
GenerateTaskTargets(${EXERCISE})

# export variables
set(OUTPUT_FILES ${OUTPUT_FILES} PARENT_SCOPE)
set(STATEMENT_PDFS ${STATEMENT_PDFS} PARENT_SCOPE)

