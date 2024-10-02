#pragma once;
#include "../input.h"
#include "../inventory.h"
#include "../ui.h"

class RemoveItemUi {
    InventoryImpl& inventory;
    bool running = true;

public:
    explicit RemoveItemUi(InventoryImpl &inventory): inventory(inventory) {
    }

    void display() {
        wstring itemId = L"";
        Item *item = nullptr;

        while (running) {
            clearScreen();
            printTopBorder();
            printEmptySpace();
            printCenteredText(L"Remove Item");
            printEmptySpace();

            if (item == nullptr) {
                printEmptySpace();
                printCenteredText(L"Enter item id:");
                printEmptySpace();
            } else {
                const auto headers = vector<wstring>{
                    L"Id",
                    L"Name",
                    L"Category",
                    L"Quantity",
                    L"Price",
                };
                auto itemsStrings = vector<vector<wstring> >{};
                vector singleRow = {
                    item->getId(),
                    item->getName(),
                    getCategoryName(item->getCategory()),
                    to_wstring(item->getQuantity()),
                    to_wstring(item->getPrice()),
                };
                itemsStrings.push_back(singleRow);
                printTable(headers, itemsStrings);
            }

            printEmptySpace();
            printCenteredText(L"Type \"back\" to go back.");
            printEmptySpace();

            if (item != nullptr) {
                printCenteredText(L"Type \"remove\" to remove the item.");
                printEmptySpace();
            }

            printBottomBorder();

            const auto input = getInput();
            if (input == L"back") {
                running = false;
                break;
            }


            if (item == nullptr) {
                itemId = input;
                try {
                    const auto searched = inventory.searchItem(itemId);
                    item = new Item(
                      searched
                    );
                } catch (const invalid_argument &e) {
                    showNotice(L"Item not found.");
                }

            } else if (input == L"remove") {
                inventory.removeItem(itemId);
                item = nullptr;
                running = false;

                showNotice(L"Item removed.");
            }
        }
    }
};
