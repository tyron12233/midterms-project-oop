#include <iostream>
#include <conio.h>

#include "inventory_ui.h"

using namespace std;







int main() {
    setlocale(LC_ALL, "");

    const InventoryImpl inventory_impl;
    InventoryUi ui(inventory_impl);
    ui.display();
}
