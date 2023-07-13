set(LIB_SOURCES
  aes_helper.c
  aes_lib.c
)

set(MAIN_SOURCES
  aes_main.c
  aes_lib.c
  aes_helper.c
)

set(HEADERS
  ${CONFIG_HEADER}
  include/aes_helper.h
  include/aes_lib.h
)

add_executable(main ${HEADERS} ${MAIN_SOURCES})

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/aes_helper.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/aes_lib.h DESTINATION include)

add_custom_target(run
  COMMAND main
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "run generated main in ${CMAKE_CURRENT_SOURCE_DIR}"
  SOURCES ${MAIN_SOURCES}
)
