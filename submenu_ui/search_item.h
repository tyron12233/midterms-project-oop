#pragma once
#include "../input.h"
#include "../inventory.h"
#include "../ui.h"

using namespace std;

class SearchItemUi {
private:
    InventoryImpl &inventory;
    bool running = true;

public:
    explicit SearchItemUi(InventoryImpl &inventory) : inventory(inventory) {
    }

    void display() {
        wstring itemId = L"";
        Item *item = nullptr;

        while (running) {
            clearScreen();
            printTopBorder();
            printEmptySpace();
            printCenteredText(L"Search Item");
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
            printBottomBorder();

            const auto input = getInput();
            if (input == L"back") {
                running = false;
                break;
            }
            if (item == nullptr) {
                itemId = input;
                try {
                    auto searchedItem = inventory.searchItem(itemId);
                    item = new Item(
                        searchedItem
                    );
                } catch (const invalid_argument &e) {
                    showNotice(L"Item not found.");
                }
            }
        }
    }
};
