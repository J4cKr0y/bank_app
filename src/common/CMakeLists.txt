add_library(common_lib status.c)
target_include_directories(common_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})