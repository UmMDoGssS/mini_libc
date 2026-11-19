cmake_minimum_required(VERSION 3.21)

set(work_directory "${CMAKE_CURRENT_BINARY_DIR}")
if(ISOLATE_FILES)
    string(RANDOM LENGTH 16 ALPHABET 0123456789abcdef suffix)
    set(work_directory "${CMAKE_CURRENT_BINARY_DIR}/mini-libc-test-${suffix}")
    file(MAKE_DIRECTORY "${work_directory}")
endif()

execute_process(
    COMMAND "${EXECUTABLE}"
    WORKING_DIRECTORY "${work_directory}"
    RESULT_VARIABLE status
    OUTPUT_VARIABLE output
)

if(ISOLATE_FILES)
    file(REMOVE_RECURSE "${work_directory}")
endif()

if(NOT status STREQUAL EXPECTED_STATUS)
    message(FATAL_ERROR "${EXECUTABLE} exited with status ${status}, expected ${EXPECTED_STATUS}")
endif()

if(DEFINED EXPECTED_OUTPUT AND NOT output STREQUAL "${EXPECTED_OUTPUT}\n")
    message(FATAL_ERROR "${EXECUTABLE} produced unexpected output: [${output}]")
endif()

execute_process(
    COMMAND "${CMAKE_COMMAND}" -E env LC_ALL=C "${READELF}" -lW "${EXECUTABLE}"
    OUTPUT_VARIABLE program_headers
    COMMAND_ERROR_IS_FATAL ANY
)
if(program_headers MATCHES "(^|\n)[ \t]*INTERP[ \t]")
    message(FATAL_ERROR "${EXECUTABLE} has an ELF interpreter")
endif()

execute_process(
    COMMAND "${CMAKE_COMMAND}" -E env LC_ALL=C "${READELF}" -dW "${EXECUTABLE}"
    OUTPUT_VARIABLE dynamic_entries
    COMMAND_ERROR_IS_FATAL ANY
)
if(dynamic_entries MATCHES "[(]NEEDED[)]")
    message(FATAL_ERROR "${EXECUTABLE} has dynamic dependencies")
endif()

execute_process(
    COMMAND "${CMAKE_COMMAND}" -E env LC_ALL=C "${NM}" -u "${EXECUTABLE}"
    OUTPUT_VARIABLE undefined_symbols
    OUTPUT_STRIP_TRAILING_WHITESPACE
    COMMAND_ERROR_IS_FATAL ANY
)
if(NOT undefined_symbols STREQUAL "")
    message(FATAL_ERROR "${EXECUTABLE} has unresolved symbols:\n${undefined_symbols}")
endif()
