#ifndef FILEWORKER_H
#define FILEWORKER_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>

class fileWorker
{
private:
    char* filename;
    std::string str;
public:
    fileWorker(char* filename);
    std::string getStr();
    void readData();
};

#endif // FILEWORKER_H
