#pragma once

/**
* 	Copyright (C) 2021 Sergey A. Salata. All rights reserved.
*
*	This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <string>
#include <vector>

/**
* Helper class with utility methods
*/
class Utils
{
public :
	static std::string loadFile(const std::string& fileName);
	static unsigned char* loadFile(const char* fileName, size_t& len);
	static std::string toBig(const std::string& txt);
	static char toBigChar(char ch);
	static std::string removeNonChar(const std::string& txt);
	static bool isChar(char ch);
	static void printIntArray(int* data, int sz);
	static void printFloatArray(float* data, int sz);

	static float calcAverage(const std::vector<float> data);
	static size_t getMaximalIndex(float* data, size_t sz);
	static size_t getMinimalIndex(float* data, size_t sz);

	static std::string generateChars(char ch, size_t len);


};

