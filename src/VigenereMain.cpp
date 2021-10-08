
#include "CipherTestUnit.h"
#include "Utils.h"

#include <iostream>
#include <cstring>

#include "VigenereCipher.h"

/**
*   Run self tests
*   @return 0 if success
*/
int runTests() {
    CipherTestUnit testUnit;
    int ret;

    if (!testUnit.runAllTests()) {
        std::cout << "All tests passed OK" << std::endl;
        ret = 0;
    }
    else {
        std::cerr << "Some tests failed" << std::endl;
        ret = 1;
    }
    return ret;
}

/**
* Print out program usage parameters
*/
void showUsage() {
    std::cerr << "Usage: Vigenere <test|decrypt> [input text file]" << std::endl;
}

/**
*   Calculate IOC of provided file
*   @param fileName - name of file
*   @return 0 if success
*/
int calcIOC(const char* fileName) {
    std::string input = Utils::loadFile(fileName);
    if (input.empty()) return 1;

    std::cout << "Loaded " << input.size() << " bytes from [" << fileName << "]" << std::endl;
    float ioc = VigenereCipher::calcIOC(input);
    std::cout << "IOC = " << ioc << std::endl;

    return 0;
}

/**
*   Decrypt file. Print out result to console
*   @param fileName - name of file
*   @return 0 if success
*/
int decryptFile(const char* fileName) {
    std::string encrypted = Utils::loadFile(fileName);
    if (encrypted.empty()) return 1;

    std::cout << "Loaded " << encrypted.size() << " bytes from [" << fileName << "]" << std::endl;
        
    VigenereCipher ch;
    std::string result;
    std::string key;
    int res = ch.decrypt(encrypted, key, result);
    if (!res) {
        std::cout << "Successfully decrypted text: [" << result << "]" << std::endl;
        std::cout << "Key: [" << key << "]" << std::endl;
    }
    else {
        std::cerr << "Could not decrypt text" << std::endl;
    }
    return 0;
}
/**
*   Applicaiton entry point
*   Process command line arguments and perform action
*   @param argc - number of command line arguments (including binary name)
*   @param argv - command line arguments array
*   @return 0 if successul exit
*/
int main(int argc, char *argv[]) {
    if (argc < 2) {
        showUsage();
        return 1;
    }

    if (!strcmp(argv[1], "test"))
        return runTests();

    if (!strcmp(argv[1], "ioc")) {
        if (argc == 3)
             return calcIOC(argv[2]);
        showUsage();
    }
    if (!strcmp(argv[1], "decrypt")) {
        if(argc==3) 
            return decryptFile(argv[2]); 
        showUsage();
    }

    return 0; 
}