#include "VigenereCipher.h"

#include "Utils.h"
#include <iostream>


/**
* Construct object and inialize internal tables
*/
VigenereCipher::VigenereCipher() {
    initTable();
}

/**
*   Destructor
*/
VigenereCipher::~VigenereCipher() {
}

/**
* Initialize Vigenere table
*/
void VigenereCipher::initTable() {
    int i, j, k;
    k = 0;

    for (i = 0; i < NUM_OF_LETTERS; i++) {
        k = i;
        for (j = 0; j < NUM_OF_LETTERS; j++) {
            vigenereTable[i][j] = 'A' + k;
            k++;
            if (k == NUM_OF_LETTERS) k = 0;
        }
    }

    // can be loaded from file as well
    englishFreqs['A' - 'A'] = 8.15f;
    englishFreqs['B' - 'A'] = 1.44f;
    englishFreqs['C' - 'A'] = 2.76f;
    englishFreqs['D' - 'A'] = 3.79f;
    englishFreqs['E' - 'A'] = 13.11f;
    englishFreqs['F' - 'A'] = 2.92f;
    englishFreqs['G' - 'A'] = 1.99f;
    englishFreqs['H' - 'A'] = 5.26f;
    englishFreqs['I' - 'A'] = 6.35f;
    englishFreqs['J' - 'A'] = 0.13f;
    englishFreqs['K' - 'A'] = 0.42f;
    englishFreqs['L' - 'A'] = 3.39f;
    englishFreqs['M' - 'A'] = 2.54f;
    englishFreqs['N' - 'A'] = 7.10f;
    englishFreqs['O' - 'A'] = 8.00f;
    englishFreqs['P' - 'A'] = 1.98f;
    englishFreqs['Q' - 'A'] = 0.12f;
    englishFreqs['R' - 'A'] = 6.83f;
    englishFreqs['S' - 'A'] = 6.10f;
    englishFreqs['T' - 'A'] = 10.47f;
    englishFreqs['U' - 'A'] = 2.46f;
    englishFreqs['V' - 'A'] = 0.92f;
    englishFreqs['W' - 'A'] = 1.54f;
    englishFreqs['X' - 'A'] = 0.17f;
    englishFreqs['Y' - 'A'] = 1.98f;
    englishFreqs['Z' - 'A'] = 0.08f;
}

/**
*   Decrypt message with provided key
*   @param msg - message to decrypt
*   @param key - key to use for decryption
*   @return - decrypted text
*/
std::string VigenereCipher::decryptWithKey(const std::string& msg, const std::string& key) {
    std::string keyExt = extendKey(key, msg.size());

    std::string decrypt;
    for (size_t i = 0U; i < msg.size(); i++) {
        char messageChar = msg[i];
        char keyChar = keyExt[i];

        decrypt += decryptChar(messageChar, keyChar);

    }
    return decrypt;
}

/**
*   Decrypt single char using Vigenere table
*   @param messageChar - character from message to decrypt
*   @param keyChar - char from key
*   @return decrypted character
*/
char VigenereCipher::decryptChar(char messageChar, char keyChar) {
    for (size_t j = 0; j < NUM_OF_LETTERS; j++) {
        if (vigenereTable[j][keyChar - 'A'] == messageChar) {
            return (char)('A' + j);
        }
    }
    return '\0';
}

/**
*   Encrypt message with provided key
*   @param msg - message to decrypt
*   @param key - key to use for encryption
*   @return - encrypted text
*/
std::string VigenereCipher::encrypt(const std::string& msg, const std::string& key) {
    std::string keyExt = extendKey(key, msg.size());

    int n = NUM_OF_LETTERS;
    std::string encrypt;
    for (size_t i = 0U; i < msg.size(); i++) {
        encrypt += vigenereTable[msg[i] - 'A'][keyExt[i] - 'A'];
    }
    return encrypt;
}


/**
* Extend key to required size. If required size < key length
* @param key - key to extend
* @param size - required size of key
* @return extened key
*/
std::string VigenereCipher::extendKey(const std::string& key, size_t size) {
    if (size < key.size()) {
        return key.substr(0, size);
    }
    std::string result = key;
    int k = 0;
    for (size_t i = key.size(); i < size; i++) {
        result += key[k++];
        k %= key.size();
    }
    return result;
}


/**
*   Try to decrypt message without known key
*   @param msg [IN] - message to decrypt
*   @param key [OUT] - key used for encryption
*   @param result [OUT] - decrypted text
*   @return - 0 if success
*/
int VigenereCipher::decrypt(const std::string& _msg, std::string& key, std::string& result) {

    std::string msg = Utils::removeNonChar(_msg);
    msg = Utils::toBig(msg);

    float ioc[13];

// 1. determine key length
//  calculcate IOC for all key lengthes 2-12, take maximal value
    for (int keyLength = 2; keyLength <= 12; keyLength++) {        
        ioc[keyLength] = calcAverageIoCForKeyLength(msg, keyLength);  //calcIOC(seq);
     //   std::cout << "IOC [" << keyLength << "]=" << ioc[keyLength] << std::endl;
    } // for

    size_t keyLength = Utils::getMaximalIndex(ioc, 13);
    std::cout << "### Probable key length: " << keyLength << " ###" << std::endl;

    // 2. find every letter in key be frequency analyzis
    char* keyBuffer = (char*)calloc(keyLength, 1);
    
    for (size_t i = 0; i < keyLength; i++) {
        // guessing key[i] char
        std::string seq = buildSequence(msg, (int)keyLength, (int)i);

        float chiSquares[NUM_OF_LETTERS];
        for (char ch = 'A'; ch <= 'Z'; ch++) {
            std::string tmpKey = Utils::generateChars(ch, keyLength);            
            std::string deciphered = decryptWithKey(seq, tmpKey);

            float chiSquare = VigenereCipher::calcChiSquare(deciphered);
            chiSquares[ch - 'A'] = chiSquare;
        }
    //    Utils::printFloatArray(chiSquares, NUM_OF_LETTERS);
        int minIndex = (int)Utils::getMinimalIndex(chiSquares, NUM_OF_LETTERS);
        char decChar = 'A' + minIndex;
    //    std::cout << "Min index is " << minIndex << ", so character is [" << decChar << "]" << std::endl;
        keyBuffer[i] = decChar;
    }

    key.assign(keyBuffer, keyLength);
    free(keyBuffer);

    result = decryptWithKey(msg, key);

    return 0;
}

/**
*   Build all possible sequences for give key length, calculate IOC for all and return average
*   @param msg - input message
*   @param keyLength - length of key
*   @return average IOC
*/
float VigenereCipher::calcAverageIoCForKeyLength(const std::string& msg, int keyLength) {
    // number of sequences
    int n = keyLength - 1;
    std::vector<float> ioc;
    for (int startIndex = 0; startIndex <= n; startIndex++) {
        std::string seq = buildSequence(msg, keyLength, startIndex);
        float value = calcIOC(seq);
        ioc.push_back(value);
    }
    return Utils::calcAverage(ioc);
}

/**
* Calculate Index of Coincidence for provided text
*   @param _text - input text
*   @return IOC value
*/
float VigenereCipher::calcIOC(const std::string& text) {
    // numbers of letters occurance 
    int n[NUM_OF_LETTERS];

    // prepare and clean input text
    std::string txt = Utils::toBig(Utils::removeNonChar(text));
 //   std::cout << "[" << txt << "]" << std::endl;

    VigenereCipher::calcFrequency(txt, n);
 //   Utils::printIntArray(n, NUM_OF_LETTERS);

    float ic = 0.f;
    size_t N = txt.size();

    for (int i = 0; i < NUM_OF_LETTERS; i++) {
        ic += (float)(n[i]*(n[i]-1)) / (float)(N*(N-1));
    }
    return ic;
}

/**
* Build sequence of eveny 'period' char
* 'ABCDEF' period=3 gives 'ACE'
*   @param txt - input text
*   @param period - period to extract
*   @param start - start index (0..period-1)
*   @return result sequence
*/
std::string VigenereCipher::buildSequence(const std::string txt, int period, int start) {
    std::string result = "";
    if (start >= period) {
        return result;
    }
    for (size_t i = 0; i < txt.size()-start; i+=period) {
        result += txt[i+start];
    }
    return result;
}

/**
*   Calculate Chi-Square char frequency probablity comapre to english
*   @param text - input message
*   @return chi square value
*/
float  VigenereCipher::calcChiSquare(const std::string& text) {
    int freq[NUM_OF_LETTERS];
    VigenereCipher::calcFrequency(text, freq);

    float expectedFreq[NUM_OF_LETTERS];
    size_t N = text.size();
    for (int i = 0; i < NUM_OF_LETTERS; i++) {
        expectedFreq[i] = ((float)englishFreqs[i] * (float)N / 100.f);
    }

    float chi = 0.f;
    for (char i = 0; i < NUM_OF_LETTERS; i++) {
        if (expectedFreq[i] != 0) {
            float value = (float)(freq[i] - expectedFreq[i]) * (freq[i] - expectedFreq[i]) / (float)(expectedFreq[i]);
            chi += value;
        }
    }
    return chi;
}
/**
*   Calculate number of letter occurance in text
*	@param [IN] txt - input text
*	@param [OUT] freq - array with frequencies of occurance (nubmbers)
*/
void VigenereCipher::calcFrequency(const std::string& txt, int* freq) {
    for (int i = 0; i < NUM_OF_LETTERS; i++) freq[i] = 0;

    for (size_t i = 0; i < txt.size(); i++) {
        char ch = txt[i];
        freq[ch - 'A'] ++;
    }
}