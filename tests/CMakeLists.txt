include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
set(HEADERS 
  ${CONFIG_HEADER}
  munit.h
)

set(TEST_SOURCES
  munit.c
  aes_helper_tests.c
)

add_executable(aes_helper_tests ${TEST_SOURCES} ${HEADERS})
target_link_libraries(aes_helper_tests aes_helper)

add_custom_target(test
  COMMAND aes_helper_tests
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "run generated aes_helper_tests in ${CMAKE_CURRENT_SOURCE_DIR}"
  SOURCES ${TEST_SOURCES}
)