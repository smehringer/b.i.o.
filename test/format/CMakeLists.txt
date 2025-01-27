cmake_minimum_required (VERSION 3.10)
project (bio_format_test CXX)

find_program(CLANG_FORMAT "clang-format-14")

if (CLANG_FORMAT STREQUAL "CLANG_FORMAT-NOTFOUND")
    find_program(CLANG_FORMAT "clang-format")
endif()

if (NOT CLANG_FORMAT STREQUAL "CLANG_FORMAT-NOTFOUND")
    add_custom_target (check_library "find" "${CMAKE_CURRENT_SOURCE_DIR}/../../include/bio/" "-name" "'*.hpp'" "-exec"
                       ${CLANG_FORMAT} "-style=file" "-n" "-Werror" "{}" "\;"
                       COMMENT "Checking the library with clang-format.")

    add_custom_target (check_unit_tests "find" "${CMAKE_CURRENT_SOURCE_DIR}/../unit/" "-name" "'*.cpp'" "-exec"
                       ${CLANG_FORMAT} "-style=file" "-n" "-Werror" "{}" "\;"
                       COMMENT "Checking the unit tests with clang-format.")

    add_custom_target (format_library "find" "${CMAKE_CURRENT_SOURCE_DIR}/../../include/bio/" "-name" "'*.hpp'" "-exec"
                       ${CLANG_FORMAT} "-style=file" "-i" "{}" "\;"
                       COMMENT "Format the library with clang-format.")

    add_custom_target (format_unit_tests "find" "${CMAKE_CURRENT_SOURCE_DIR}/../unit/" "-name" "'*.cpp'" "-exec"
                       ${CLANG_FORMAT} "-style=file" "-i" "{}" "\;"
                       COMMENT "Format the unit tests with clang-format.")
endif()
