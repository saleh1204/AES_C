include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
set(HEADERS 
  ${CONFIG_HEADER}
  munit.h
)

set(TEST_SOURCES
  aes_helper_tests.c
  munit.c
  ../src/aes_helper.c
)

add_executable(aes_helper_tests ${TEST_SOURCES} ${HEADERS})

add_custom_target(test
  COMMAND aes_helper_tests
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "run generated aes_helper_tests in ${CMAKE_CURRENT_SOURCE_DIR}"
  SOURCES ${TEST_SOURCES}
)
