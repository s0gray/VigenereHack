
#include "CipherTestUnit.h"
#include "VigenereCipher.h"
#include "Utils.h"

#include <iostream>

#include <math.h>

#define ASSERT_COMPARE(x,y) if(x.compare(y)) return 1;
#define ASSERT(x)	if(x) return x;
#define ASSERT_EQ(x,y) if(x!=y) return 1;

CipherTestUnit::CipherTestUnit() {
}

CipherTestUnit::~CipherTestUnit() {
}

/**
*	Test decryption with test vectors
*	@return 0 if success 
*/
int CipherTestUnit::testDecrypt() {
	VigenereCipher cipher;

	std::string plain = "HELLOWORLD";
	std::string encrypted = "AIDEHAGKEH";
	std::string key = "TEST";
	std::string decrypted = cipher.decryptWithKey(encrypted, key);

	std::cout << std::endl << "### Test Decrypt ###" << std::endl;

	std::cout << "Encrypted text : [" << encrypted << "]" << std::endl;
	std::cout << "key : [" << key << "]" << std::endl;
	std::cout << "Decrypted text : [" << decrypted << "]" << std::endl;
	std::cout << "Plain text : [" << plain << "]" << std::endl;

	ASSERT_COMPARE(decrypted, plain);

	return 0;
}

/**
*	Test encryption with test vectors
*	@return 0 if success
*/
int CipherTestUnit::testEncrypt() {
	VigenereCipher cipher;

	std::string plain = "HELLOWORLD";
	std::string ciphered = "AIDEHAGKEH";
	std::string key = "TEST";
	std::string encrypted = cipher.encrypt(plain, key);

	std::cout << std::endl << "### Test Encrypt ###" << std::endl;

	std::cout << "Plain text : [" << plain << "]" << std::endl;
	std::cout << "key : [" << key << "]" << std::endl;

	std::cout << "Encrypted text : [" << encrypted << "]" << std::endl;
	std::cout << "Ciphered text : [" << ciphered << "]" << std::endl;

	ASSERT_COMPARE(encrypted, ciphered);
	return 0;
}

/**
*	Execute all tests one by one, stop on first fail
*	@return 0 if success
*/
int CipherTestUnit::runAllTests() {
	ASSERT(testEncrypt());
	std::cout << "testEncrypt PASSED OK" << std::endl;

	ASSERT(testDecrypt());
	std::cout << "testDecrypt PASSED OK" << std::endl;

	ASSERT(testToBig());
	std::cout << "testToBig PASSED OK" << std::endl;

	ASSERT(testCalcIOC());
	std::cout << "testCalcIOC PASSED OK" << std::endl;
	
	ASSERT(testBuildSequence());
	std::cout << "testBuildSequence PASSED OK" << std::endl;

	ASSERT(testCalcAverage());
	std::cout << "testCalcAverage PASSED OK" << std::endl;
	
	ASSERT(testCalcChiSquare());
	std::cout << "testCalcChiSquare PASSED OK" << std::endl;
	
	ASSERT(testHack());
	std::cout << "testHack PASSED OK" << std::endl;

	return 0;
}

int CipherTestUnit::testToBig() {
	std::cout << std::endl << "### Test toBig  ###" << std::endl;

	std::string input = "aAbbBBBc,.d";
	std::string exptected = "AABBBBBC,.D";

	std::cout << "Input text : [" << input << "]" << std::endl;

	std::string output =  Utils::toBig(input);
	std::cout << "Output text : [" << output << "]" << std::endl;

	ASSERT_COMPARE(output, exptected);
	return 0;
}

int CipherTestUnit::testCalcIOC() {
	std::cout << std::endl << "### Test calc IOC  ###" << std::endl;

	std::string input = "AACDEFGHDDDDKLMNOPQRST";
	float ioc = VigenereCipher::calcIOC(input);
	float expectedIoc = 0.047619f;

	std::cout << "IoC=" << ioc << std::endl;
	if( fabs(ioc-expectedIoc)<0.001f)
		return 0;
	return 1;
}

int CipherTestUnit::testBuildSequence() {
	std::cout << std::endl << "### Test Build Sequence  ###" << std::endl;

	std::string input = "AACDEFGHDDDDKLMNOPQRST";
	std::string expected2_0 = "ACEGDDKMOQS";
	std::string expected2_1 = "ADFHDDLNPRT";

	std::string expected3 = "ADGDKNQT";
	std::string expected4 = "AEDKOS";

	std::string result2_0 = VigenereCipher::buildSequence(input, 2, 0);
	std::cout << "Result2_0: [" << result2_0 << "]" << std::endl;
	std::string result2_1 = VigenereCipher::buildSequence(input, 2, 1);
	std::cout << "Result2_1: [" << result2_1 << "]" << std::endl;

	std::string result3 = VigenereCipher::buildSequence(input, 3, 0);
	std::cout << "Result3 : [" << result3 << "]" << std::endl;

	std::string result4 = VigenereCipher::buildSequence(input, 4, 0);
	std::cout << "Result4 : [" << result4 << "]" << std::endl;

	ASSERT_COMPARE(expected2_0, result2_0);
	ASSERT_COMPARE(expected2_1, result2_1);

	ASSERT_COMPARE(expected3, expected3);
	ASSERT_COMPARE(expected4, expected4);

	return 0;
}

int CipherTestUnit::testHack() {
	std::string key, result;
	VigenereCipher cipher;

	std::string txt = Utils::loadFile("ioc3.txt");
	if (txt.empty()) {
		std::cerr << "Can't load test file" << std::endl;
		return 1;
	}


	int res = cipher.decrypt(txt, key, result);

	std::cout << "key = [" << key << "]" << std::endl;
	std::cout << "result = [" << result << "]" << std::endl;

	std::string expectedKey = "CIAHERS";
	ASSERT_COMPARE(key, expectedKey);


	txt = Utils::loadFile("test2.enc");
	if (txt.empty()) {
		std::cerr << "Can't load test file" << std::endl;
		return 1;
	}
	res = cipher.decrypt(txt, key, result);
	ASSERT(res);

	std::cout << "key = [" << key << "]" << std::endl;
	std::cout << "result = [" << result << "]" << std::endl;

	expectedKey = Utils::loadFile("test2.key");
	std::cout << "expectedKey = [" << expectedKey << "]" << std::endl;

	std::string expectedResult = Utils::toBig( Utils::removeNonChar( Utils::loadFile("test2.txt") ));
	std::cout << "expectedResult = [" << expectedResult << "]" << std::endl;

	ASSERT_COMPARE(key, expectedKey);
	ASSERT_COMPARE(result, expectedResult);

	return 0;
}

int CipherTestUnit::testCalcAverage() {
	std::cout << std::endl << "### Test Calculate Average  ###" << std::endl;

	std::vector<float> data;
	data.push_back(1.f);
	data.push_back(2.f);
	data.push_back(3.f);
	data.push_back(4.f);
	float expected = 2.5f;

	float result = Utils::calcAverage(data);
	ASSERT_EQ(expected, result);

	return 0;
}

int CipherTestUnit::testCalcChiSquare() {
	std::cout << std::endl << "### Test Calculate Chi Square  ###" << std::endl;

	std::string input1 = "VURZJUGRGGUGVGJQKEOAGUGKKQVWQP";
	float expected1 = 595.42f;
	std::string input2 = "UTQYITFQFFTFUFIPJDNZFTFJJPUVPO";
	float expected2 = 466.86f;

	VigenereCipher ch;
	float result1 = ch.calcChiSquare(input1);
	std::cout << "Chi-Square ["<< input1 << "] = " << result1 << " expected = " << expected1 << std::endl;

	float result2 = ch.calcChiSquare(input2);
	std::cout << "Chi-Square [" << input2 << "] = " << result2 << " expected = " << expected2 << std::endl;

	if (fabs(expected1 - result1) > 20) return 1;
	if (fabs(expected2 - result2) > 20) return 1;


	return 0;


}
