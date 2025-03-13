#include <iostream>
#include <fstream>

unsigned getFileLen(std::ifstream& strm) {
	strm.seekg(0, std::ios::end);
	unsigned len = strm.tellg();
	strm.seekg(0, std::ios::beg);
	return len;
}

bool isEndOfWord(char ch) {
	if (ch == ' ' || ch == '\0')
		return true;
	return false;
}

bool isKeyWord(char* fileContent, const char* keyWord, unsigned index) {
	unsigned keyWordIndex = 0;
	for (; !isEndOfWord(fileContent[index]); index++) {
		if (fileContent[index] != keyWord[keyWordIndex++])
			return false;
	}
	return true;
}

unsigned editedArrLen(char* fileContent, const char* keyWord) {
	unsigned counter = 0;
	for (unsigned i = 0; fileContent[i] != '\0'; i++) {
		if (fileContent[i] == keyWord[0] && isKeyWord(fileContent, keyWord, i)) {
			counter += strlen(keyWord) + 1;
		}
	}
	return strlen(fileContent) - counter;
}

void moveIndexToNextWord(char* arr, unsigned& index) {
	while (!isEndOfWord(arr[index]))
		index++;
	if (arr[index] != '\0')
		index++;
}

char* readFile(std::ifstream& strm) {
	unsigned len = getFileLen(strm);
	char* arr = new char[len + 1];
	unsigned index = 0;
	while (!strm.eof()) {
		arr[index++] = strm.get();
	}
	arr[len] = '\0';
	return arr;
}

char* removeKeyWord(std::ifstream& strm, const char* keyWord) {
	char* fileContent = readFile(strm);
	unsigned len = editedArrLen(fileContent, keyWord);
	char* edited = new char[len + 1];
	edited[len] = '\0';
	unsigned fileIndex = 0;
	for (unsigned i = 0; edited[i] != '\0'; i++) {
		if (fileContent[fileIndex] == keyWord[0] && isKeyWord(fileContent, keyWord, fileIndex)) {
			moveIndexToNextWord(fileContent, fileIndex);
		}
		edited[i] = fileContent[fileIndex++];
	}
	return edited;
}

int main()
{
	char arr[] = { "mazna batio mazna" };
	std::ofstream ofstream("test.txt");
	for (unsigned i = 0; arr[i] != '\0'; i++) {
		ofstream.put(arr[i]);
	}
	ofstream.close();

	std::ifstream ifstream("test.txt");
	
	char* text = removeKeyWord(ifstream, "batio");
	std::cout << text;
}