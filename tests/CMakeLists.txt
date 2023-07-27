include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../build/src)

enable_testing()

set(HEADERS
  munit.h
  ../src/include/aes_helper.h
  ../src/include/aes_lib.h
)
set(TESTS_LIB_SRC
  munit
)

set(TESTS_LIBS
  aes_helper
  aes_lib
  munit
)
set(aes_helper_tests_sources
  aes_helper_tests.c
)

set(aes_lib_tests_sources
  aes_lib_tests.c
)

add_library(munit SHARED munit.c)

add_executable(aes_helper_tests ${aes_helper_tests_sources} ${HEADERS})
add_executable(aes_lib_tests ${aes_lib_tests_sources} ${HEADERS})

target_link_libraries(aes_helper_tests PUBLIC munit aes_helper)
target_link_libraries(aes_lib_tests PUBLIC munit aes_lib)

add_test(NAME t_aes_helper COMMAND aes_helper_tests)
add_test(NAME t_aes_lib COMMAND aes_lib_tests)
