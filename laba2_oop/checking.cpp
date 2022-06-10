#include "checking.h"
#include<QDebug>

string Validator::deleteSpaces(string str)
{
    while (str.find(' ') != string::npos) {
        str.erase(str.find(' '), 1);
    }
    while (str.find("\n") != string::npos) {
        str.erase(str.find("\n"), 1);
    }
    while (str.find("\t") != string::npos) {
        str.erase(str.find("\t"), 1);
    }
    return str;
}

void Validator::checkBrackets(string& str)
{
    string s(str);
    int countF = 0, countS = 0;
    int* sqBr = new int[s.length() * sizeof(int)];
    int* figBr = new int[s.length() * sizeof(int)];
    for(int i =0; i<int(s.length()); i++){
        if (s[i] == '{') {
            figBr[countF] = i;
            countF++;
        }else if (s[i] == '[') {
            sqBr[countS] = i;
            countS++;
        }else if (s[i] == '}') {
            if (figBr[countF - 1] > sqBr[countS - 1]) {
                countF--;
            }else
                throw JsonException("[ находится между {}", i);
        }else if (s[i] == ']') {
            if (figBr[countF - 1] < sqBr[countS - 1]) {
                countS--;
            }else
                throw JsonException("{ находится между []", i);
        }
    }
    if (countF != 0)
        throw JsonException("потеряли }", 0);
    if (countS != 0)
        throw JsonException("потеряли ]", 0);
    delete[] sqBr;
    delete[] figBr;
}

string* reallocString(string* strList, int count)
{
    string* strListNew = new string[count+1];
    for(int i = 0; i<count; i++){
        strListNew[i]=strList[i];
    }
    return strListNew;
}

string* Validator::checkName(string str, int* i, string* strList, int countOfNames)
{
    *i = *i + 1;
    int startPos = *i;
    *i=str.find('"', *i)+1;
    if ((int)str.find_first_of("{}[]:,", startPos) < *i)
        throw JsonException("вы потеряли \" после имени переменной", *i);
    else if (str[*i] != ':'){
        throw JsonException("вы потеряли :", *i);
    }
    string* strlist = reallocString(strList, countOfNames);
    string f = str.substr(startPos, *i-startPos);
    findSameNames(strList, f, i, countOfNames);
    strList=reallocString(strlist, countOfNames);
    strList[countOfNames]=f;
    delete[]strlist;
    return strList;
}

void Validator::findSameNames(string* list, string str, int* pos, int count)
{
    for(int i=0; i<count; i++){
        if(list[i]==str){
            string as = list[i];
            throw JsonException("повторяющееся имя значения", *pos);
    }
    }
}

void Validator::checkStr(string str, int* i)
{
    int count;
    *i=*i+1;
    if(str.find_first_of('"', *i) < str.find_first_of("{}[]:,", *i))
        count=str.find('"', *i);
    else
        throw JsonException("забыли , ", *i);
    qDebug()<<count;
    qDebug()<<*i;
    *i=count;
}

void Validator::checkNum(string str, int* i)
{
    string num;
    if(str.find_first_of(",[]{}", *i)!=string::npos){
        if(str.find_first_of(",[]{}", *i)==*i)
            throw JsonException("неопределяемый формат номера", *i);
        num = str.substr(*i, str.find_first_of(",[]{}", *i)-*i);
        if(num.find(".")!=-1)
            if(to_string(stof(num))!=num)
                throw JsonException("неопределяемый формат номера", *i);
        else
            if(to_string(stoi(num))!=num)
                throw JsonException("неопределяемый формат номера", *i);
    }else{
        num=str.substr(*i);
        if(num.find(".")!=-1)
            if(to_string(stof(num))!=num)
                throw JsonException("неопределяемый формат номера", *i);
        else
            if(to_string(stoi(num))!=num)
                throw JsonException("неопределяемый формат номера", *i);
    }
    *i=*i+num.length()-1;
}

void Validator::checkBool(string str, int* i)
{
    if(str.substr(*i, 4)=="true");
    else if(str.substr(*i, 5)=="false");
    else if(str.substr(*i, 4)=="null");
    else
        throw JsonException("error: строчка с \" \"", *i);
}

int findCloseBracket(string s, int openBr, char opBr, char clBr)
{
    string str(s);
    int pose;
    while(str.find(opBr, openBr)!=string::npos){
        pose = str.find(clBr, str.find(opBr, openBr));
        str.replace(pose, 1, "5");
        str.replace(str.find(opBr, openBr), 1, "8");
    }
    pose=str.find(clBr, openBr);
    return pose;
}

void Validator::check_value_(string object, int* count)
{
    if(object[*count]=='t' || object[*count]=='f' || object[*count]=='n'){
        checkBool(object, count);
    }
    else if(object[*count]=='"'){
        checkStr(object, count);
    }
    else if(object[*count]=='{'){
        checkObject(object, count);
    }
    else if(object[*count]=='['){
        checkMassiv(object, count);
    }
    else{
        checkNum(object, count);
    }
}

void Validator::checkObject(string str, int* i)
{
    string* strList = new string[1];
    int countOfNames = 0;
    *i=*i+1;
    int pose=findCloseBracket(str, *i, '{', '}');
    string object=str.substr(*i, pose-*i);
    if(object.length()!=0){
        int count = 0;
        while(count<object.length()-1){
            if(object[count]=='"'){
                strList=checkName(object, &count, strList, countOfNames);
                countOfNames++;
                count++;
                check_value_(object, &count);
            }else
                throw JsonException("забыли имяя ", *i+count);
            count++;
            if(object[count]!=',' && count<object.length()-1)
                throw JsonException("забыли ,", *i+count);
            count++;
        }
        *i=*i+count-1;
    }
    delete[]strList;
}

//Array
void Validator::checkMassiv(string str, int* i)
{
    *i=*i+1;
    string mass=str.substr(*i, findCloseBracket(str, *i, '[', ']')-*i);
    int count=0;
    if(mass.length()!=0){
        while(count<mass.length()-1){
            check_value_(mass, &count);
            count++;
            if(mass[count]!=',' && count<mass.length()-1)
                throw JsonException("забыли ,", *i+count);
            count++;
        }
        *i=*i+count+1;
    }else
        *i=*i+1;
}

void Validator::checkValue1(string str)
{
    str=deleteSpaces(str);
    this->str=str;
    for (int i = 0; i<int(str.length()); i++) {
        check_value_(str, &i);
    }
}

Validator::Validator(std::string s)
{
    this->str.append(s);
}

std::string Validator::getStr()
{
    return this->str;
}
