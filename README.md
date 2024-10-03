# Midterm Project: Inventory Management System

## Project Overview

This project is an Inventory Management System implemented in C++. It provides a user interface to interact with the inventory, allowing users to add, display, search, update, and remove items.


### Key Files and Directories

- **.gitignore**: Specifies files and directories to be ignored by Git.
- **.idea/**: Contains project-specific settings and configurations for the IDE.
- **CMakeLists.txt**: CMake configuration file for building the project.
- **input.h**: Header file for handling user input.
- **inventory_ui.h**: Header file for the `InventoryUi` class, which provides a user interface to interact with the inventory.
- **inventory.h**: Header file for the `InventoryImpl` class, which manages the inventory data. Here is the OOP and Ecapsulation implementation.
- **main.cpp**: Main entry point of the application.
- **README.md**: This file, providing an overview of the project.
- **submenu_ui/**: Directory containing header files for various UI components:
  - **add_item_ui.h**: UI for adding items.
  - **display_items.h**: UI for displaying items.
  - **low_stock_items.h**: UI for displaying low stock items.
  - **remove_item.h**: UI for removing items.
  - **search_item.h**: UI for searching items.
  - **update_item.h**: UI for updating items.
- **ui.h**: Header file for common UI functions.

## Building the Project

To build the project, ensure you have CMake and the required dependencies installed. Then, run the following commands:

```sh
mkdir -p cmake-build-debug
cd cmake-build-debug
cmake ..
make