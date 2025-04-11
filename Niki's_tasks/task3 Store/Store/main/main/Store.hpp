#include "Item.hpp"
#pragma once

class Store {
public:
    Store(){};
    Store(const Item* data, unsigned itemsCount) {
        this->itemsCount = itemsCount;
        if (itemsCount == 0) {
            this->capacity = 1;
        }
        else {
            this->capacity = itemsCount * 2;
        }
        this->items = new Item * [this->capacity];
        for (unsigned i = 0; i < itemsCount; i++) {
            this->items[i] = new Item(data[i]);
        }
    }

    Store(const Store& other) {
        copy(other);
    }

    ~Store() {
        clearData();
    }

    const Item* const* getItems() const {
        return items;
    }

    unsigned getItemsCount() const {
        return this->itemsCount;
    }

    Store operator=(const Store& other) {
        if (this == &other) {
            return *this;
        }
        clearData();
        copy(other);
        return *this;
    }

    void pushItem(const Item& data) {
        if (this->capacity == this->itemsCount) {
            try {
                if (this->capacity == 0)
                    this->capacity = 1;

                resize();
            }
            catch (const std::exception& e) {
                std::cerr << "Can't add more items to store! No items were added";
                return;
            }
        }
        items[this->itemsCount++] = new Item(data); //Will work bcs when adding the items "cap = itemsCount" =>
                                //=> itemsCount points to last saved elem
    }

    void pushItems(const Item* const* items, unsigned amount) {
        for (unsigned i = 0; i < amount; i++) {
            pushItem(*items[i]);
        }
    }

    Item* popItem() {
        if (itemsCount == 0) {
            std::cout << "No more items to pop";
            return nullptr;
        }
        Item* temp = items[--itemsCount]->clone();
        delete items[itemsCount];
        items[itemsCount] = nullptr;
        return temp;
    }

private:
    void resize() {
        Item** temp = items;
        this->capacity *= 2;
        this->items = new Item * [this->capacity];
        for (size_t i = 0; i < this->itemsCount; i++) {
            items[i] = temp[i];
            temp[i] = nullptr;
        }
        delete[] temp;
    }

    void copy(const Store& other) {
        this->itemsCount = other.itemsCount;
        this->capacity = other.capacity;
        this->items = new Item * [this->capacity];
        for (unsigned i = 0; i < itemsCount; i++) {
            this->items[i] = new Item(*other.getItems()[i]);
        }
    }

    void clearData() noexcept {
        delete[] this->items;
        this->itemsCount = 0;
        this->capacity = 0;
        this->items = nullptr;
    }

    Item** items = nullptr;
    unsigned capacity = 0;
    unsigned itemsCount = 0;
};