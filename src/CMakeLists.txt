include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(LIB_SOURCES
  aes_helper
  aes_lib
)

set(MAIN_SOURCES
  aes_main.c
)

set(HEADERS
  ${CONFIG_HEADER}
  include/aes_helper.h
  include/aes_lib.h
)

add_library(aes_helper SHARED aes_helper.c)
add_library(aes_lib SHARED aes_lib.c aes_helper.c)

add_executable(main ${HEADERS} ${MAIN_SOURCES})

target_link_libraries(main PRIVATE aes_lib)

add_custom_target(run
  COMMAND main
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "run generated main in ${CMAKE_CURRENT_SOURCE_DIR}"
  SOURCES ${MAIN_SOURCES}
)
