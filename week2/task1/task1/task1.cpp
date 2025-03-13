#include <iostream>
#include <fstream>


void print_cpp(std::ifstream& strm) {
	if (!strm.is_open()) {
		std::cout << "File not open or wrong path!";
		return;
	}

	while (!strm.eof()) {
		char temp = strm.get();
		std::cout << temp;
	}
	strm.clear();
	strm.seekg(0);
}

int main()
{
	std::ifstream cpp("task1.cpp");
	print_cpp(cpp);


}
