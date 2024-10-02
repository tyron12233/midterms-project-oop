#pragma once
#include "../input.h"
#include "../inventory.h"
#include "../ui.h"

class AddItemUi {
    InventoryImpl& inventory;
    bool running = true;

public:
    explicit AddItemUi(InventoryImpl &inventory): inventory(inventory) {
    }

    void display() {
        Category category = NONE;
        int categoryIndex = 0;

        const vector<wstring> categoryNames = {
            L"Clothing",
            L"Electronics",
            L"Entertainment",
        };

        wstring itemId = L"";
        int quantity = 0;
        wstring itemName = L"";
        double price = 0;

        while (running) {
            clearScreen();

            printTopBorder();
            printEmptySpace();
            printCenteredText(L"Add Item");
            printEmptySpace();
            printEmptySpace();

            if (category == NONE) {
                printCenteredText(L"Select a category:");
                printEmptySpace();


                printCenteredText(getSelectionString(categoryNames, categoryIndex));
            } else {
                wstring name = getCategoryName(category);
                printCenteredText(L"Category: " + name);
            }

            if (category != NONE && itemId.empty()) {
                printCenteredText(L"Enter item id:");
            } else if (!itemId.empty()) {
                printCenteredText(L"Id: " + itemId);
            }

            if (category != NONE && !itemId.empty() && quantity == 0) {
                printCenteredText(L"Enter quantity:");
            } else if (quantity != 0) {
                printCenteredText(L"Quantity: " + to_wstring(quantity));
            }

            if (category != NONE && !itemId.empty() && quantity > 0 && itemName.empty()) {
                printCenteredText(L"Enter item name:");
            } else if (!itemName.empty()) {
                printCenteredText(L"Name: " + itemName);
            }

            if (category != NONE && !itemId.empty() && quantity > 0 && !itemName.empty() && price == 0) {
                printCenteredText(L"Enter price:");
            } else if (price > 0) {
                printCenteredText(L"Price: " + to_wstring(price));
            }


            printEmptySpace();
            printMovementHint();
            printEmptySpace();
            printBottomBorder();

            // input


            if (category == NONE) {
                const auto key = getArrowKey();
                // handle input for category
                if (key == KEY_LEFT) {
                    if (categoryIndex > 0) {
                        categoryIndex--;
                    }
                } else if (key == KEY_RIGHT) {
                    if (categoryIndex < categoryNames.size() - 1) {
                        categoryIndex++;
                    }
                } else if (key == KEY_ENTER) {
                    category = static_cast<Category>(categoryIndex + 1);
                }
            } else if (itemId.empty()) {
                const auto itemIdInput = getInput();
                if (!itemIdInput.empty()) {
                    itemId = itemIdInput;

                    // let's see if there's already an item with this id.
                    try {
                        inventory.searchItem(itemId);
                        showNotice(L"An item with this id already exists. Please enter a different id.");
                        itemId = L"";
                    } catch (const invalid_argument &e) {
                        // do nothing
                    }
                }
            } else if (quantity == 0) {
                // handle input for quantity
                quantity = getNumberInput();
            } else if (itemName.empty()) {
                // handle input for item name
                itemName = getInput();
            } else {
                // handle input for price
                price = getDoubleInput();

                const Item item(category, itemName, itemId, quantity, price);
                inventory.addItem(item);
                showNotice(L"Item added successfully.");

                running = false;
            }
        }
    }

    void printCurrentItemInfo(Category category, wstring name, int quantity, double price) {
    }

    wstring getCategoryName(Category category) {
        switch (category) {
            case CLOTHING:
                return L"Clothing";
            case ELECTRONICS:
                return L"Electronics";
            case ENTERTAINMENT:
                return L"Entertainment";
            default:
                return L"";
        }
    }
};
