cmake_minimum_required(VERSION 3.28)
project(midterm_project_oop)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})



add_executable(midterm_project_oop main.cpp
        input.h
        ui.h
        inventory.h
        inventory_ui.h
        submenu_ui/add_item_ui.h
        submenu_ui/display_items.h
        submenu_ui/display_items.h
        submenu_ui/search_item.h
        submenu_ui/remove_item.h
        submenu_ui/update_item.h
        submenu_ui/update_item.h
        submenu_ui/low_stock_items.h
)
target_link_libraries(midterm_project_oop ${CURSES_LIBRARIES})