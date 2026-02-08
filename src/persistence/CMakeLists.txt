add_library(persistence_lib csv_driver.c)

target_include_directories(persistence_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

# La persistance a besoin de connaître la structure Account
target_link_libraries(persistence_lib PRIVATE account_lib)
