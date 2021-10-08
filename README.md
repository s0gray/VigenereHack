# VigenereHack
hacking vigenere cipher tool


Here is sample application for decrypting Vigenere ciphered text
using algorythm described http://practicalcryptography.com/cryptanalysis/stochastic-searching/cryptanalysis-vigenere-cipher/

First it try to determine key length searching for maximal Index of Occurence for keys with length 2-12
Then for every char in key it calculated average Chi-Square between character frequencies comparable to english alphabet 
frequencies. Lower value taken as result.



Building
========
Linux - type 'make' in folder with Makefile
Windows - open .sln file in Visual Studio 2019, build and run


Command line options:
 $ Vigerere <test|decrypt> [input text file]


Self testing
=============
 $ Vigenere test

Will start run of unit test to test components of application.
Running test requires presense of following files with test vectors in binarie's folder:
 - test2.enc
 - test2.key
 - test2.txt
 - ioc3.txt


Decryption of file
==================

 $ Vigenere decrypt [input file name]

 Decrypt provided file and show result to console output


