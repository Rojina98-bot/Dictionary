#ifndef MAIN_H
#define MAIN_H
#include<iostream>
#include<string>
#include<iterator>
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<cstdlib>
//#include<conio.h>
//#include<wchar.h>
//#include<windows.h>
#include<iomanip>
#include<climits>
#define ALPHABET_SIZE 26
using namespace std;
class trie
{
    public:
    string meaning;
    string word;
    trie* children[26];
    int isLeaf;
};
class MemoryAllocationError : public exception {
public:
    const char* what() const throw() {
        return "Memory allocation error";
    }
};
#endif


