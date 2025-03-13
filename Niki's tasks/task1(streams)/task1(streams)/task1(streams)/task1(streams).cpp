#include <iostream>
#include <fstream>

const unsigned nameLen = 10;

struct Items
{
    unsigned price = 0;
    char name[nameLen];
};


void saveToFile(std::ofstream& strm, const Items* instances, unsigned itemsCount) {
    strm.write((const char*) instances, itemsCount*sizeof(Items));
}

Items* saveToArr(std::ifstream& strm) {
    strm.seekg(0, std::ios::end);
    unsigned itemCount = strm.tellg()/sizeof(Items);
    strm.seekg(0, std::ios::beg);

    Items* arr = new Items[itemCount];
    
    strm.read((char*)arr, itemCount * sizeof(Items));
    return arr;
}

int main()
{
    std::ofstream ofstream("binary.dat", std::ios::binary);
    if (!ofstream.is_open())
        return 0;

    Items* arr = new Items[2];
    arr[0] = { 123, "123" };
    arr[1] = { 321, "321" };

    saveToFile(ofstream, arr, 2);
    ofstream.close();

    delete[] arr;

    std::ifstream ifstream("binary.dat", std::ios::binary);
    arr = saveToArr(ifstream);

    for (int i = 0; i < 2; i++) {
        std::cout << arr[i].price;
        std::cout << arr[i].name;
        std::cout << '\n';
    }
    delete[]arr;
}
