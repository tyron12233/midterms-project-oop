#pragma onceo
#include "../inventory.h"
#include "../ui.h"

enum UpdateOption {
    NOT_SET,
    QUANTITY_OPTION,
    PRICE_OPTION,
};

class UpdateItemUi {
private:
    InventoryImpl &inventory;
    bool running = true;
    Item *itemPtr = nullptr;

public:
    explicit UpdateItemUi(InventoryImpl &inventory): inventory(inventory) {
    }

    void display() {
        while (running) {
            clearScreen();
            printTopBorder();
            printEmptySpace();
            printCenteredText(L"Update Item");
            if (itemPtr == nullptr) {
                printCenteredText(L"Enter item id or \"back\" to go back.");
            } else {
                displayUpdateItem();
                itemPtr = nullptr;
                continue;
            }
            printEmptySpace();
            printBottomBorder();


            const auto input = getInput();
            if (input == L"back") {
                running = false;
                break;
            }

            if (input.empty()) {
                showNotice(L"Invalid input.");
                continue;
            }

            if (!itemExists(input)) {
                const wstring message = L"Item id " + input + L" not found";
                showNotice(message);
                continue;
            } else {
                itemPtr = new Item(inventory.searchItem(input));
            }
        }
    }

    void displayUpdateItem() {
        bool updateRunning = true;
        UpdateOption updateOption = NOT_SET;
        int updateOptionIndex = 0;

        while (updateRunning) {
            clearScreen();
            printTopBorder();
            printEmptySpace();
            printCenteredText(L"Updating Item");

            const auto headers = vector<wstring>{
                L"Id",
                L"Name",
                L"Category",
                L"Quantity",
                L"Price",
            };
            auto itemsStrings = vector<vector<wstring> >{};
            vector singleRow = {
                itemPtr->getId(),
                itemPtr->getName(),
                getCategoryName(itemPtr->getCategory()),
                to_wstring(itemPtr->getQuantity()),
                to_wstring(itemPtr->getPrice()),
            };
            itemsStrings.push_back(singleRow);
            printTable(headers, itemsStrings);
            printEmptySpace();

            if (updateOption == NOT_SET) {
                const auto updateOptions = vector<wstring>{
                    L"Quantity",
                    L"Price",
                };
                printCenteredText(L"Select an option to update:");
                printEmptySpace();
                const auto optionString = getSelectionString(updateOptions, updateOptionIndex);
                printCenteredText(optionString);
            } else {
                // update option is set, display the input prompt
                if (updateOption == QUANTITY_OPTION) {
                    printCenteredText(L"Enter new quantity:");
                } else if (updateOption == PRICE_OPTION) {
                    printCenteredText(L"Enter new price:");
                }
            }

            printBottomBorder();


            // handling
            if (updateOption == NOT_SET) {
                const auto key = getKeyPressBlocking();
                if (key == KEY_LEFT) {
                    updateOptionIndex = (updateOptionIndex - 1 + 2) % 2;
                } else if (key == KEY_RIGHT) {
                    updateOptionIndex = (updateOptionIndex + 1) % 2;
                } else if (key == KEY_ENTER) {
                    updateOption = static_cast<UpdateOption>(updateOptionIndex + 1);
                }
            } else {
                // updating price or quantity
                const auto input = getInput();
                if (input.empty()) {
                    showNotice(L"Invalid input.");
                    continue;
                }

                // show notice that price is updated from old value to new value
                if (updateOption == QUANTITY_OPTION) {
                    const auto oldQuantity = itemPtr->getQuantity();
                    const auto newQuantity = stoi(input);
                    const auto message = L"Quantity updated from " + to_wstring(oldQuantity) + L" to " + to_wstring(
                                             newQuantity);
                    showNotice(message);
                    inventory.updateItem(
                        itemPtr->getId(),
                        {
                            itemPtr->getCategory(),
                            itemPtr->getName(),
                            itemPtr->getId(),
                            newQuantity,
                            itemPtr->getPrice()
                        }
                    );
                } else if (updateOption == PRICE_OPTION) {
                    const auto oldPrice = itemPtr->getPrice();
                    const auto newPrice = stod(input);
                    const auto message = L"Price updated from " + to_wstring(oldPrice) + L" to " + to_wstring(newPrice);
                    showNotice(message);
                    inventory.updateItem(
                        itemPtr->getId(),
                        {
                            itemPtr->getCategory(),
                            itemPtr->getName(),
                            itemPtr->getId(),
                            itemPtr->getQuantity(),
                            newPrice
                        }
                    );
                }

                updateRunning = false;
            }
        }
    }

    bool itemExists(const wstring &itemId) {
        try {
            // this will throw if the item is not found
            inventory.searchItem(itemId);
            return true;
        } catch (const invalid_argument &e) {
            return false;
        }
    }
};
