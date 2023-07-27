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

foreach(lib IN LISTS LIB_SOURCES)
  add_library(${lib} ${lib}.c)
endforeach()

add_executable(main ${HEADERS} ${MAIN_SOURCES})

foreach(lib IN LISTS LIB_SOURCES)
  target_link_libraries(main PRIVATE ${lib})
endforeach()

add_custom_target(run
  COMMAND main
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "run generated main in ${CMAKE_CURRENT_SOURCE_DIR}"
  SOURCES ${MAIN_SOURCES}
)
