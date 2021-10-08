#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>

/**
* Load text file from disk returns contents of empty string if some error happens
* @param fileName - name of file to read
* @return file contents of empty string
*/
std::string Utils::loadFile(const std::string& fileName) {
	std::string result = "";
	size_t len;
	unsigned char* buffer = Utils::loadFile(fileName.c_str(), len);
	if (!buffer) {
		return result;
	}
	result.assign((const char*)buffer, len);
	free(buffer);
	return result;
}

/**
*	Load file from disk
*	@param fileName - name of file
*	@param len - returned length of loaded data
*	@return pointer to allocated memory buffer with loaded data
*/
unsigned char* Utils::loadFile(const char* fileName, size_t& len)
{
	std::ifstream::pos_type size;
	unsigned char* memblock = 0;
	len = 0;

	std::ifstream file(fileName, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		size = file.tellg();
		len = (unsigned int)size;
		memblock = new unsigned char[len];
		file.seekg(0, std::ios::beg);
		file.read((char*)memblock, size);
		file.close();
	}
	return memblock;
}

/**
*	Convert string to HIGH letters
*	@param txt - input text
*	@return BIG LETTER text
*/
std::string Utils::toBig(const std::string& txt)
{
	std::string result = "";
	for (size_t i = 0; i < txt.size(); i++) {
		result += toBigChar(txt.at(i));
	}
	return result;
}

/**
*	Convert character to BIG CASE
*	@param ch - input character
*	@return BIG CHARACTER
*/
char Utils::toBigChar(char ch) {
	if (ch >= 'a' && ch <= 'z')
		return ch - ('a' - 'A');
	else
		return ch;
}

/**
*	Remove all non char letter
*	@param txt - input text
*	@return filtered text
*/
std::string Utils::removeNonChar(const std::string& txt) {
	std::string result = "";
	for (size_t i = 0; i < txt.size(); i++) {
		char ch = txt.at(i);
		if(isChar(ch))
		result += ch;
	}
	return result;
}

/**
* Determine is provided char is letter
*	@param ch - character to test
*	@return TRUE is character is letter
*/
bool Utils::isChar(char ch) {
	if (ch >= 'A' && ch <= 'Z') return true;
	if (ch >= 'a' && ch <= 'z') return true;
	return false;
}

/**
*	Print out  integer array
*	@param data - input integer array
*	@param sz - size of array
*/
void Utils::printIntArray(int* data, int sz) {
	for (int i = 0; i < sz; i++) {
		std::cout << "N[" << i << "] {"<< (char)('A' +i) << "} = " << data[i] << std::endl;
	}
}

/**
*	Print out  integer array
*	@param data - input float array
*	@param sz - size of array
*/
void Utils::printFloatArray(float* data, int sz) {
	for (int i = 0; i < sz; i++) {
		std::cout << "N[" << i << "] {" << (char)('A' + i) << "} = " << data[i] << std::endl;
	}
}


/**
*	Calculate average of std::vector
*	@param data - input vector of data
*	@return average value
*/
float Utils::calcAverage(const std::vector<float> data) {
	if (data.empty()) return 0.f;

	float sum = 0.f;
	for (float a : data) {
		sum += a;
	}
	return sum / (float)data.size();
}

/**
* Find maximal value in data and return index of maximal value
*	@param data - input array of float
*	@param sz - size of input array
*	@return index of maximal value in array
*/
size_t Utils::getMaximalIndex(float* data, size_t sz) {
	if (!data || sz == 0) return -1;

	float max = 0.f;
	int idx = -1;
	for (size_t i = 0; i < sz; i++) {
		if ( (data[i] > max) || idx<0 ) {
			max = data[i];
			idx = (int) i;
		}
	}
	return (size_t)idx;
}

/**
* Find minimal value in data and return index of minimal value
*	@param data - input array of float
*	@param sz - size of input array
*	@return index of minimal value in array
*/
size_t Utils::getMinimalIndex(float* data, size_t sz) {
	if (!data || sz == 0) return -1;

	float min = 0.f;
	int idx = -1;
	for (size_t i = 0; i < sz; i++) {
		if ((data[i] < min) || idx == -1) {
			min = data[i];
			idx = (int)i;
		}
	}
	return (size_t) idx;
}

/**
*	Generate string with same character and give length, ('A', 4) -> 'AAAA'
*	@param ch - character to fill string
*	@param len - required length of output string
*	@return string 
*/
std::string Utils::generateChars(char ch, size_t len) {
	std::string str = "";
	for (size_t i = 0; i < len; i++) str += ch;
	return str;
}


