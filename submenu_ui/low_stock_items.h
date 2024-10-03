#pragma once
#include <conio.h>

#include "../inventory.h"
#include "../ui.h"

class LowStockItemsUi {

private:
    InventoryImpl &inventory;
    bool running = false;

public:
    explicit LowStockItemsUi(InventoryImpl &inventory) : inventory(inventory) {

    }

    void display() {
        clearScreen();

        printTopBorder();
        printEmptySpace();
        printCenteredText(L"Low Stock Items");
        printEmptySpace();
        vector<Item> items = inventory.getItems();
        vector<Item> lowStockItems;
        for (auto &item: items) {
            if (item.getQuantity() < 5) {
                lowStockItems.push_back(item);
            }
        }

        if (lowStockItems.empty()) {
            showNotice(L"No low stock items.");
            return;
        }

        const auto headers = vector<wstring>{
            L"Id",
            L"Name",
            L"Category",
            L"Quantity",
            L"Price",
        };
        auto itemsStrings = vector<vector<wstring>>{};
        for (auto &item: lowStockItems) {
            vector singleRow = {
                item.getId(),
                item.getName(),
                getCategoryName(item.getCategory()),
                to_wstring(item.getQuantity()),
                to_wstring(item.getPrice()),
            };
            itemsStrings.emplace_back(singleRow);
        }
        printTable(headers, itemsStrings);

        printEmptySpace();
        printCenteredText(L"Press enter to continue");
        printEmptySpace();
        printBottomBorder();
        getch();
    }
};
