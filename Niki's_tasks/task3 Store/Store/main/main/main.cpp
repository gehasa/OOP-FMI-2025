#include <iostream>
#include <fstream>
#include "FileHandler.hpp"

void createSampleItemsFileTxt(const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Couldn't open file for writing.\n";
        return;
    }

    out << "3\n";
    out << "4\nMilk\n2.50\n";
    out << "5\nBread\n1.30\n";
    out << "6\nButter\n3.99\n";

    out.close();
    std::cout << "Sample TXT file created: " << filename << '\n';
}

void testReadFromTxt(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Couldn't open file to read.\n";
        return;
    }

    FileHandler fh;
    try {
        Store store(fh.readFromTxtFile(in));
        std::cout << "\nLoaded store from TXT:\n";
        const Item* const* items = store.getItems();
        for (unsigned i = 0; i < store.getItemsCount(); ++i) {
            std::cout << "- " << items[i]->getName() << ": $" << items[i]->getPrice() << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error reading from TXT file: " << e.what() << '\n';
    }
}

void testSaveLoadBinary(const std::string& filename) {
    Item item1((char*)"Apple", 0.99f);
    Item item2((char*)"Orange", 1.29f);
    Item item3((char*)"Banana", 0.75f);

    Item items[] = { item1, item2, item3 };
    Store store(items, 3);

    FileHandler fh;

    std::ofstream outBin(filename, std::ios::binary);
    fh.saveToBinaryFile(outBin, &store);
    outBin.close();
    std::cout << " Saved store to binary file: " << filename << '\n';

    std::ifstream inBin(filename, std::ios::binary);
    try {
        Store loadedStore = fh.readFromBinaryFile(inBin);
        std::cout << "\nLoaded store from BIN:\n";
        const Item* const* items = loadedStore.getItems();
        for (unsigned i = 0; i < loadedStore.getItemsCount(); ++i) {
            std::cout << "- " << items[i]->getName() << ": $" << items[i]->getPrice() << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error reading from BIN file: " << e.what() << '\n';
    }
    inBin.close();
}

void displayItemsFromBinaryFile(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open binary file: " << filename << '\n';
        return;
    }

    FileHandler fileHandler;
    try {
        Store store = fileHandler.readFromBinaryFile(in);
        const Item* const* items = store.getItems();
        unsigned itemCount = store.getItemsCount();

        std::cout << "Items loaded from binary file:\n";
        for (unsigned i = 0; i < itemCount; ++i) {
            std::cout << "- Name: " << items[i]->getName()
                << ", Price: $" << items[i]->getPrice() << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error reading from binary file: " << e.what() << '\n';
    }

    in.close();
}


int main() {
    std::string txtFile = "items.txt";
    std::string binFile = "items.bin";

    createSampleItemsFileTxt(txtFile);
    testReadFromTxt(txtFile);
    testSaveLoadBinary(binFile);
    displayItemsFromBinaryFile(binFile);
    return 0;
}
