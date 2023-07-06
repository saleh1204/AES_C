set(LIB_SOURCES
  aes_helper.c
  aes_lib.c
)

set(MAIN_SOURCES
  aes_main.c
)

set(HEADERS 
  ${CONFIG_HEADER}
  include/aes_helper.h
  include/aes_lib.h
)

add_library(aes_helper STATIC ${LIB_SOURCES} ${HEADERS})
add_library(aes_lib STATIC ${LIB_SOURCES} ${HEADERS})

add_executable(main ${HEADERS} ${MAIN_SOURCES})
target_link_libraries(main aes_helper aes_lib)

install(TARGETS aes_helper
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/aes_helper.h DESTINATION include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/aes_lib.h DESTINATION include)

add_custom_target(run
  COMMAND main
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "run generated main in ${CMAKE_CURRENT_SOURCE_DIR}"
  SOURCES ${MAIN_SOURCES}
)