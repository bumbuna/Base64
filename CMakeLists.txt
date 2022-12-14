cmake_minimum_required(VERSION 3.0)

project(BASE64 LANGUAGES C DESCRIPTION "BASE64 encode/decoder" VERSION 1.0.0.0)

add_library(base64 STATIC lib/base64.c)

add_executable(base64ed src/base64e.c)

target_link_libraries(base64ed base64)

enable_testing()

install(TARGETS base64ed DESTINATION bin)
install(TARGETS base64 DESTINATION lib)
execute_process(COMMAND /usr/bin/date
OUTPUT_VARIABLE BASE64_COMPILE_TIME_OUT)
string(STRIP ${BASE64_COMPILE_TIME_OUT} BASE64_COMPILE_TIME)
configure_file(include/base64config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/base64config.h)

function(base64test str fname)
		file(WRITE ${CMAKE_BINARY_DIR}/${fname} ${str})
		execute_process(COMMAND base64 -w 0
						OUTPUT_VARIABLE out
						INPUT_FILE ${fname}
						OUTPUT_FILE "${fname}.64"
						WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
				)
		string(STRIP "${out}" out)
		add_test(NAME "TEST_${fname}"
				COMMAND base64ed ${fname}
				WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
				)
		set_tests_properties(TEST_${fname} PROPERTIES PASS_REGULAR_EXPRESSION "${out}")
		add_test(NAME "TEST_${fname}_d"
				COMMAND base64ed -d "${fname}.64"
				WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		)
		set_tests_properties("TEST_${fname}_d" PROPERTIES PASS_REGULAR_EXPRESSION "^${str}")

endfunction()

file(STRINGS test/testfile.txt lines)
set(lineCount 0)
foreach(line ${lines})
	string(STRIP ${line} line)
	base64test(${line} ${lineCount})
	math(EXPR lineCount "${lineCount}+1")
endforeach()
