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

#include <vector>
#include <string>

/// number of letters in alphabet
#define NUM_OF_LETTERS  26

class VigenereCipher
{
public:
	VigenereCipher();
	virtual ~VigenereCipher();

	std::string decryptWithKey(const std::string& msg, const std::string& key);
	int decrypt(const std::string& msg, std::string& key, std::string& result);

	std::string encrypt(const std::string& msg, const std::string& key);
	static float calcIOC(const std::string& text);
	static std::string buildSequence(const std::string txt, int period, int start);
	static std::string extendKey(const std::string& key, size_t size);
	static float calcAverageIoCForKeyLength(const std::string& msg, int keyLength);

	float  calcChiSquare(const std::string& text);
	static void calcFrequency(const std::string& txt, int* freq);

protected:
	char decryptChar(char encryptedChar, char keyChar);

private:
	void initTable();

	
	char vigenereTable[NUM_OF_LETTERS][NUM_OF_LETTERS];
	float englishFreqs[NUM_OF_LETTERS];
};

