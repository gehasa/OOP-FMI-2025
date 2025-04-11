#pragma once
#include "store.hpp"
#include <fstream>
#include <string>

class FileHandler {
public:
    void saveToBinaryFile(std::ofstream& strm, Store* store) {
        if (!strm.is_open()) {
            std::cout << "Bad stream!";
            return;
        }
        unsigned len = store->getItemsCount();
        strm.write((const char*)(&len), sizeof(len));
        const Item* const* items = store->getItems();
        for (size_t i = 0; i < len; i++) {
            const char* const name = items[i]->getName();
            if (name == nullptr) {
                std::cout << "Invalid item";
                continue;
            }
            float price = items[i]->getPrice();
            unsigned nameLen = items[i]->getNameLen();
            strm.write((const char*)&nameLen, sizeof(nameLen));
            strm.write((const char*)name, nameLen);
            strm.write((const char*)&price, sizeof(price));
            strm.flush();
        }
    }

    void saveToTxtFile(std::ofstream& strm, const Store& store) {
        if (!strm.is_open()) {
            throw std::invalid_argument("Bad stream!");
        }
        const Item* const* items = store.getItems();
        if (items == nullptr) {
            throw std::invalid_argument("Invalid store given!");
        }
        unsigned itemsCount = store.getItemsCount();
        strm << itemsCount << '\n';
        for (unsigned i = 0; i < itemsCount; i++) {
            std::cout << items[i]->getName() << ' ';
            strm << items[i]->getNameLen() << '\n' <<
                items[i]->getName() << '\n' <<
                items[i]->getPrice() << '\n';
            strm.flush();
        }
        return;
    }

    Store readFromTxtFile(std::ifstream& strm) {
        if (!strm) {
            throw std::invalid_argument("Bad stream!");
        }

        const unsigned long fileSize = getFileSizeInBytes(strm);
        if (fileSize < 1) {
            throw std::invalid_argument("Empty txt file");
        }
        
        unsigned itemsCount = 0;
        strm >> itemsCount;
        if (itemsCount < 1) {
            throw std::invalid_argument("No items in file");
        }
        Item** items = new Item * [itemsCount];
        for (size_t i = 0; i < itemsCount; i++) {
            unsigned nameLen;
            strm >> nameLen;
            strm.ignore();
            char* name = new char[nameLen + 1];
            strm.getline(name, '\n');
            name[nameLen] = '\0';
            float price = 0;
            strm >> price;
            strm.ignore();
            try {
                items[i] = new Item(name, price);
                delete[] name;
            }
            catch (const std::exception& e) {
                clearItems(items, itemsCount);
                delete[] name;
                throw e;
            }
        }
        Store store;
		store.pushItems(items, itemsCount);
        return store;
    }

    Store readFromBinaryFile(std::ifstream& strm) {
        if (!strm) {
            throw std::invalid_argument("Bad stream!");
        }

        unsigned itemsCount = 0;
        strm.read((char*)(&itemsCount), sizeof(itemsCount));
        if (itemsCount == 0) {
            std::cerr << "Empty bin file!";
            Store store;
            return store;
        }
        Store store;
        for (unsigned i = 0; i < itemsCount;i++) {
            unsigned nameLen = 0;
            strm.read((char*)(&nameLen), sizeof(nameLen));
            char* name = new char[nameLen + 1];
            strm.read(name, nameLen);
            name[nameLen] = '\0';
            float price = 0;
            strm.read((char*)(&price), sizeof(price));
            store.pushItem(Item(name, price));
            delete[] name;
        }
        return store;
    }

    const unsigned long getFileSizeInBytes(std::ifstream& strm) {
        unsigned long curr = strm.tellg();
        strm.seekg(0, std::ios::end);
        unsigned long end = strm.tellg();
        strm.seekg(curr, std::ios::beg);
        strm.clear();
        return end;
    }

    void clearItems(Item** toClear, unsigned count) {
        for (unsigned i = 0; i < count; i++) {
            delete toClear[i];
        }
        delete[] toClear;
    }
private:

};