#pragma once

#include <functional>

#include "input.h"
#include "inventory.h"
#include "ui.h"
#include "submenu_ui/add_item_ui.h"
#include "submenu_ui/display_items.h"
#include "submenu_ui/remove_item.h"
#include "submenu_ui/search_item.h"

using namespace std;

class Action {
public:
    wstring title;
    function<void()> action;

    Action(wstring title, const function<void()> &action) : title(std::move(title)), action(action) {
    }
};

// wraps the inventory class, providing a user interface
// to interact with the inventory
class InventoryUi {
private:
    bool running = true;
    InventoryImpl inventory;

public:
    explicit InventoryUi(const InventoryImpl &inventory) {
        this->inventory = inventory;
    }


    static void printOptionTitle(const wstring &title, bool selected) {
        wstring text;
        if (selected) {
            text += L">";
        } else {
            text += L"";
        }
        text += title;
        printCenteredText(text);
    }

    void display() {
        int currentOption = 1;


        const auto options = vector<Action>{
            {
                L"Add item",
                [this] {
                    AddItemUi addItemUi(inventory);
                    addItemUi.display();
                }
            },

            {
                L"Display Items",
                [this] {
                    DisplayItemsUi displayItemsUi(inventory);
                    displayItemsUi.display();
                }
            },

            {
                L"Search Item",
                [this] {
                    SearchItemUi searchItemUi(inventory);
                    searchItemUi.display();
                }
            },

            {
                L"Remove Item",
                [this] {
                    RemoveItemUi removeItemUi(inventory);
                    removeItemUi.display();
                }
            },

            {L"Exit", [this] { running = false; }},
        };


        while (running) {
            clearScreen();

            printTopBorder();
            printEmptySpace();
            printCenteredText(L"Welcome to Tyron Scott's Inventory");
            printEmptySpace();
            printEmptySpace();
            printCenteredText(L"Choose an option:");
            printEmptySpace();
            for (int i = 1; i <= options.size(); i++) {
                printOptionTitle(options[i - 1].title, i == currentOption);
            }
            printBottomBorder();


            switch (getKeyPressBlocking()) {
                case KEY_UP:
                    if (currentOption > 1) {
                        currentOption--;
                    }
                    break;
                case KEY_DOWN:
                    if (currentOption < options.size()) {
                        currentOption++;
                    }
                    break;
                case KEY_ENTER:
                    const auto &chosenAction = options[currentOption - 1];
                    chosenAction.action();
                    break;
            }
        }
    }
};
