#ifndef EnValues_H
#define EnValues_H

#include <any>
#include <iostream>
/*
struct MyIntpS{
    int size{};
    int *ertek{};
};
struct MyFloatpS{
    int size;
    float *ertek;
};
struct MyDoublepS{
    int size;
    double *ertek;
};

struct MyCharpS{
    int size;
    char *ertek;
};
struct MyStringpS{
    int size;
    std::string *ertek;
};
struct MyBoolpS{
    int size;
    bool *ertek;
};
*/

class EnValues
{
public:
    //EnValues();
    virtual ~EnValues(){
        std::cout<<"";
    }
    //visszateriti a valtozo tipusat, megy direkt
    //std::string getType(std::any value);
    //visszateriti a valtozot strinnge alakitva,
    //az elso 2 byte a hossz, 
    //egy char a tipus
    //tobbi simma karakter
    //alosztaly kell elvegezze
    std::string virtual getString(std::string value);
    std::string virtual getString(int value);
    //kodolas
    std::string IntToString(int value);
};
/*
class MyInt:public EnValues
{
public:
    ~MyInt(){}
    std::string getString(std::any value);
};

class MyFloat:public EnValues
{
public:
    ~MyFloat(){}
    std::string getString(std::any value);
};

class MyDouble:public EnValues
{
public:
    ~MyDouble(){}
    std::string getString(std::any value);
};

class MyChar:public EnValues
{
public:
    ~MyChar(){}
    std::string getString(std::any value);
};

class MyString:public EnValues
{
public:
    ~MyString(){}
    std::string getString(std::any value);
};

class MyBool:public EnValues
{
public:
    ~MyBool(){}
    std::string getString(std::any value);
};

class MyIntP:public EnValues
{
public:
    ~MyIntP(){}
    std::string getString(std::any value);
};

class MyFloatP:public EnValues
{
public:
    ~MyFloatP(){}
    std::string getString(std::any value);
};

class MyDoubleP:public EnValues
{
public:
    ~MyDoubleP(){}
    std::string getString(std::any value);
};
class MyCharP:public EnValues
{
public:
    ~MyCharP(){}
    std::string getString(std::any value);
};
class MyStringP:public EnValues
{
public:
    ~MyStringP(){}
    std::string getString(std::any value);
};
class MyBoolP:public EnValues
{
public:
    ~MyBoolP(){}
    std::string getString(std::any value);
};
*/






#endif