# On active l'automatisation de Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# On cherche Qt6
find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(bank_gui
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    dashboard.cpp 
    dashboard.h 
    dashboard.ui 
    ../main.c
)

target_link_libraries(bank_gui PRIVATE 
    Qt6::Widgets
	Qt6::Gui
    system_lib
    persistence_lib
    common_lib
    auth_lib
)
