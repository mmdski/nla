add_library(nlalib
  error.c
  exit.c
  memory.c
  string.c
)
if(NOT MSVC)
  target_link_libraries(nlalib PRIVATE m)
endif()
