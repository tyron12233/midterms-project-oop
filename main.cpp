#include <iostream>
#include <conio.h>

#include "inventory_ui.h"

using namespace std;

int main() {
    // set locale to support unicode characters
    setlocale(LC_ALL, "");

    // the main inventory object, manages the items
    const InventoryImpl inventory_impl;

    // the user interface object that displays the inventory contents
    InventoryUi ui(inventory_impl);
    ui.display();
}
