#ifndef FILEWORK_H
#define FILEWORK_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>

class fileWork
{
private:
    char* filename;
    std::string str;
public:
    fileWork(char* filename);
    std::string getStr();
    void readData();
};

#endif // FILEWORK_H
