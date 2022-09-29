cmake_minimum_required(VERSION 3.0)

project(BASE64 LANGUAGES C DESCRIPTION "BASE64 encode/decoder" VERSION 0.0)

add_library(base64 STATIC lib/base64.c)

add_executable(base64e src/base64.c)

target_link_libraries(base64e base64)

enable_testing()

function(base64test str fname)
		file(WRITE ${fname} ${str})
		execute_process(COMMAND base64 ${fname}
						OUTPUT_VARIABLE out
				)
		string(STRIP ${out} out)
		add_test(NAME "TEST_${fname}"
				COMMAND base64e ${fname}
				WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
				)
		set_tests_properties(TEST_${fname} PROPERTIES PASS_REGULAR_EXPRESSION ${out})
endfunction()

base64test("hello" 1)
base64test("meme" 2)
