add_library(system_lib memory_driver.c)

target_include_directories(system_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

# Le système a besoin de connaitre les comptes pour faire le travail
target_link_libraries(system_lib PRIVATE account_lib common_lib)
