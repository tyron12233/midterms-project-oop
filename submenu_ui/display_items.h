#pragma once
#include "../inventory.h"
#include "../ui.h"



class DisplayItemsUi {

private:
    InventoryImpl& inventory;
    bool running = true;
    Category displayCategoryType = NONE;

public:
    explicit DisplayItemsUi(InventoryImpl &inventory) : inventory(inventory) {
    }

    void display() {
        vector<Item> items = inventory.getItems();

        bool initiallyEmpty = items.empty();

        int currentY = 0;
        int filterIndex = 0;
        int sortIndex = 0;
        int orderIndex = 0;

        while (running) {
            clearScreen();
            printTopBorder();
            printEmptySpace();
            printCenteredText(L"Inventory Items");
            printEmptySpace();


            if (items.empty()) {
                showNotice(L"Inventory is empty.");

                if (initiallyEmpty) {
                    running = false;
                    break;
                }
            } else {
                const auto headers = vector<wstring>{
                    L"Id",
                    L"Name",
                    L"Category",
                    L"Quantity",
                    L"Price",
                };
                auto itemsStrings = vector<vector<wstring>>{};
                for (auto &item: items) {
                    vector singleRow = {
                        item.getId(),
                        item.getName(),
                        getCategoryName(item.getCategory()),
                        to_wstring(item.getQuantity()),
                        to_wstring(item.getPrice()),
                    };
                    itemsStrings.emplace_back(singleRow);
                }
                printEmptySpace();
                printTable(headers, itemsStrings);
            }


            printEmptySpace();

            if (currentY == 0) {
                printCenteredText(L"--Filter Options--");
            } else {
                printCenteredText(L"Filter options:");
            }
            // filtering options
            const vector<wstring> options = {
                L"None",
                L"Clothing",
                L"Electronics",
                L"Entertainment",
            };
            const auto optionsString = getSelectionString(options, filterIndex, getPrefixSuffix(currentY, 0));
            printCenteredText(optionsString);
            printEmptySpace();



            if (currentY == 1) {
                printCenteredText(L"--Sort Options--");
            } else {
                printCenteredText(L"Sort options: ");
            }
            // sorting options
            const vector<wstring> sortOptions = {
                L"Default",
                L"By Quantity",
                L"By Price",
            };
            const auto sortOptionsString = getSelectionString(sortOptions, sortIndex, getPrefixSuffix(currentY, 1));
            printCenteredText(sortOptionsString);
            printEmptySpace();



            const vector<wstring> orderOptions = {
                L"Ascending",
                L"Descending",
            };
            const auto orderOptionsString = getSelectionString(orderOptions, orderIndex, getPrefixSuffix(currentY, 2));
            printCenteredText(orderOptionsString);
            printEmptySpace();

            const auto exitOptionString = getSelectionString({L"Exit"}, currentY != 3);
            printCenteredText(exitOptionString);


            printEmptySpace();
            printBottomBorder();


            // input
            const auto key = getKeyPressBlocking();
            if (key == KEY_LEFT) {
                if (currentY == 0) {
                    // decrease filter to left
                    if (filterIndex > 0) {
                        filterIndex--;
                    }
                } else if (currentY == 1) {
                    // decrease sort to left
                    if (sortIndex > 0) {
                        sortIndex--;
                    }
                } else if (currentY == 2) {
                    // decrease order to left
                    if (orderIndex > 0) {
                        orderIndex--;
                    }
                }
            } else if (key == KEY_RIGHT) {
                if (currentY == 0) {
                    // increase filter to right
                    if (filterIndex < 3) {
                        filterIndex++;
                    }
                } else if (currentY == 1) {
                    // increase sort to right
                    if (sortIndex < 2) {
                        sortIndex++;
                    }
                } else if (currentY == 2) {
                    // increase order to right
                    if (orderIndex < 1) {
                        orderIndex++;
                    }
                }
            } else if (key == KEY_UP) {
                if (currentY > 0) {
                    currentY--;
                }
            } else if (key == KEY_DOWN) {
                if (currentY < 3) {
                    currentY++;
                }
            } else if (key == KEY_ENTER) {
                if (currentY == 0) {
                    displayCategoryType = static_cast<Category>(filterIndex);
                    try {
                        if (displayCategoryType == NONE) {
                            items = inventory.getItems();
                        } else {
                            items = inventory.getItemsByCategory(displayCategoryType);
                        }
                    } catch (const invalid_argument &e) {
                        // show no items found in category name
                        wstring message;
                        message.append(L"No items found in category: ");
                        message.append(getCategoryName(displayCategoryType));
                        showNotice(message);
                    }
                } else if (currentY == 1 || currentY == 2) {
                    bool ascending = orderIndex == 0;
                    // sort
                    try {
                        if (sortIndex == 0) {
                            items = inventory.getItems();
                        } else if (sortIndex == 1) {
                            items = inventory.getItemsSortedByQuantity(ascending);
                        } else if (sortIndex == 2) {
                            items = inventory.getItemsSortedByPrice(ascending);
                        }

                        // apply filter
                        if (displayCategoryType != NONE) {
                            for (auto it = items.begin(); it != items.end();) {
                                if (it->getCategory() != displayCategoryType) {
                                    it = items.erase(it);
                                } else {
                                    ++it;
                                }
                            }
                        }
                    } catch (const invalid_argument &e) {
                        // convert e.what to wstring
                        wstring message(e.what(), e.what() + strlen(e.what()));
                        showNotice(message);
                    }
                } else {
                    running = false;
                }

            }
        }
    }



    wstring getPrefixSuffix(int index, int supposed) {
        if (index == supposed) {
            return L"[]";
        }

        return L"()";
    }
};
