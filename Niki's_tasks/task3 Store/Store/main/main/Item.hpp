#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include "Utils.hpp"

class  Item {
public:
    Item() {};
    Item(char* name, float price) {
        setPrice(price);
        setName(name);
    }
    Item(const Item& other) {
        copy(other);
    }
    Item(Item&& other) {
        move(std::move(other));
    }
    ~Item() {
        clearData();
    }

    Item& operator=(const Item& other) noexcept {
        if (this == &other) {
            return *this;
        }
        clearData();
        copy(other);
        return *this;
    }

    Item& operator=(Item&& other) noexcept{
        if (this == &other) {
            return *this;
        }
        clearData();
        move(std::move(other));
        return *this;
    }

    Item* clone() {
        return new Item(*this);
    }

    void setPrice(float price) {
        if(Utils::validFloat(price))
            this->price = price;
    }

    void setName(char* name) {
        if (Utils::validName(name)) {
            delete[] this->name;
            this->nameLen = strlen(name);
            this->name = new char[this->nameLen + 1];
            strcpy(this->name, name);
        }
    }

    const char* const getName() const {
        if (name == nullptr) {
            return "\0";
        }
        return name;
    }
    float getPrice() const {
        return price;
    }
    unsigned getNameLen() const {
        return this->nameLen;
    }
private:
    void copy(const Item& other) {
        if (other.name == nullptr) {
            this->name = nullptr;
            this->nameLen = 0;
            this->price = 0.00;
            return;
        }
        this->nameLen = strlen(other.name);
        this->name = new char[this->nameLen + 1];
        strcpy(this->name, other.name);
        this->price = other.getPrice();
    }
    void move(Item&& other) noexcept {
        this->name = other.name;
        other.name = nullptr;
        this->nameLen = other.nameLen;
        other.nameLen = 0;
        this->price = other.price;
        other.price = 0.00;
    }
    void clearData() noexcept {
        delete[] this->name;
        this->nameLen = 0;
        this->price = 0;
        this->name = nullptr;
    }

    char* name = nullptr;
    float price = 0;
    unsigned nameLen = 0;
};