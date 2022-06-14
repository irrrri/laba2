#ifndef CHECKING_H
#define CHECKING_H

#include <string>
#include <stdexcept>

using namespace std;

#include "jsonChecker.h"

class checking
{
private:
    string str;
    void findSameNames(string* list, string str, int* pos, int count);
    void checkStr(string str, int* i);
    void checkNum(string str, int* i);
    void checkBool(string str, int* i);
    string deleteSpaces(string str);
    void checkBrackets(string& str);
    void check_value_(string object, int* count);
    void checkMassiv(string str, int* i);
    void checkObject(string str, int* i);
    string* checkName(string str, int* i, string* strList, int countOfNames);

public:

    checking(std::string s);

    std::string getStr();

    void checkValue();
};

#endif // CHECKING_H
