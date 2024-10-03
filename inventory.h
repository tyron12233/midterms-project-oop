#pragma once

#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// abstraction and encapsulation stuff is implemented here
// the inventory class is an abstract class that represents an inventory
// each level of the inventory class hierarchy adds more functionality to the inventory
// THX SIR :D

// represents the different ways to sort items,
// either by quantity or price
enum SortType {
    QUANTITY,
    PRICE
};


wstring toUpper(const wstring &str) {
    wstring upperStr = str;
    for (auto &c: upperStr) {
        c = towupper(c);
    }

    return upperStr;
}


// represents the different categories an item can belong to
// either clothing, electronics, or entertainment
enum Category {
    NONE,

    CLOTHING,

    ELECTRONICS,

    ENTERTAINMENT,


};

inline wstring getCategoryName(Category category) {
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

// represents an item in the inventory
// an item has a category, name, id, quantity, and price
class Item {
private:
    Category category;
    wstring name;
    wstring id;
    int quantity;
    double price;

public:
    Item(Category category, const wstring &name, const wstring &id, int quantity, double price) : category(category),
        name(name), id(id), quantity(quantity), price(price) {
    }

    Category getCategory() const {
        return category;
    }

    const wstring &getName() const {
        return name;
    }

    const wstring &getId() const {
        return id;
    }

    int getQuantity() const {
        return quantity;
    }

    double getPrice() const {
        return price;
    }
};


// represents an inventory
class Inventory {
public:
    virtual ~Inventory() = default;

    /**
     * Searches for an item in the inventory
     * @param id the id of the item to search for
     * @return the item with the given id
     * @throws invalid_argument if the item with the given id is not found
     */
    virtual Item searchItem(const wstring &id) = 0;

    virtual void updateItem(const wstring &id, Item newItem) = 0;

    virtual void removeItem(const wstring &id) = 0;

    virtual void addItem(Item item) = 0;

    /**
     * Sorts the items in the inventory
     * @param sortType what to sort the items by
     * @param ascending whether to sort in ascending or descending order
     */
    virtual void sortItems(SortType sortType, bool ascending) = 0;

    /**
     * @return a vector of all the items in the inventory
     */
    virtual vector<Item> getItems() = 0;
};

/**
 * Implements the basic functionality of an inventory (storage)
 * Basic functionality includes adding, removing, and updating items
 */
class BaseInventory : public Inventory {
protected:
    vector<Item> items;
public:
    Item searchItem(const wstring &id) override {
        // specific search
        for (const auto &item: items) {
            if (item.getId() == id) {
                return item;
            }
        }

        // try with case insensitive search
        for (const auto &item: items) {
            const auto upperItemId = toUpper(item.getId());
            const auto upperId = toUpper(id);

            if (upperItemId == upperId) {
                return item;
            }
        }

        throw invalid_argument("Item not found");
    }

    void addItem(const Item item) override {
        items.push_back(item);
    }

    void removeItem(const wstring &id) override {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->getId() == id) {
                items.erase(it);
                return;
            }

            if (toUpper(it->getId()) == toUpper(id)) {
                items.erase(it);
                return;
            }
        }

        throw invalid_argument("Item not found");
    }

    void updateItem(const wstring &id, Item newItem) override {
        for (auto &item: items) {
            if (item.getId() == id) {
                item = newItem;
                return;
            }

            if (toUpper(item.getId()) == toUpper(id)) {
                item = newItem;
                return;
            }
        }

        throw invalid_argument("Item not found");
    }

    vector<Item> getItems() override {
        return items;
    }
};


/**
 * Implements the sorting functionality of an inventory
 */
class SortableInventory : public BaseInventory {
public:
    // returns a vector of sorted items but not modifying the original items
    vector<Item> getItemsSortedByQuantity(const bool ascending) {
        const auto originalItems = items;
        sortItems(QUANTITY, ascending);
        const auto sortedItems = items;
        items = originalItems;
        return sortedItems;
    }

    // returns a vector of sorted items but not modifying the original items
    vector<Item> getItemsSortedByPrice(const bool ascending) {
        const auto originalItems = items;
        sortItems(PRICE, ascending);
        const auto sortedItems = items;
        items = originalItems;
        return sortedItems;
    }


    // sorts the items in the inventory, modifying the original items
    void sortItems(const SortType sortType, const bool ascending) override {
        if (sortType == QUANTITY) {
            sortByQuantity(ascending);
        } else {
            sortByPrice(ascending);
        }
    }

    void sortByQuantity(const bool ascending) {
        // bubble sort
        for (int i = 0; i < items.size() - 1; i++) {
            for (int j = 0; j < items.size() - i - 1; j++) {
                if (ascending) {
                    if (items[j].getQuantity() > items[j + 1].getQuantity()) {
                        swap(items[j], items[j + 1]);
                    }
                } else {
                    if (items[j].getQuantity() < items[j + 1].getQuantity()) {
                        swap(items[j], items[j + 1]);
                    }
                }
            }
        }
    }

    void sortByPrice(const bool ascending) {
        // bubble sort
        for (int i = 0; i < items.size() - 1; i++) {
            for (int j = 0; j < items.size() - i - 1; j++) {
                if (ascending) {
                    if (items[j].getPrice() > items[j + 1].getPrice()) {
                        swap(items[j], items[j + 1]);
                    }
                } else {
                    if (items[j].getPrice() < items[j + 1].getPrice()) {
                        swap(items[j], items[j + 1]);
                    }
                }
            }
        }
    }
};

/**
 * Adds extended functionality to the inventory such as
 * filter by type, displaying low stock items, etc.
 */
class InventoryImpl : public SortableInventory {
public:
    /**
     *
     * @return a vector of all the items in the inventory that are low in stock
     *         an item is considered low in stock if its quantity is less than 5
     */
    vector<Item> getLowStockItems() {
        vector<Item> lowStockItems;
        for (const auto &item: items) {
            if (item.getQuantity() < 5) {
                lowStockItems.push_back(item);
            }
        }

        return lowStockItems;
    }

    /**
     * 
     * @param category the category to filter by
     * @return a vector of all the items in the inventory that belong to the given category
     * @throws invalid_argument if the category is not found
     */
    vector<Item> getItemsByCategory(const Category category) {
        vector<Item> itemsByCategory;
        for (const auto &item: items) {
            if (item.getCategory() == category) {
                itemsByCategory.push_back(item);
            }
        }

        if (itemsByCategory.empty()) {
            throw invalid_argument("Category not found");
        }

        return itemsByCategory;
    }
};