#include "EnValues.h"
#include <iostream>
#include <algorithm>

using namespace std;


string EnValues::getString(string value){
    string ret1=IntToString(value.size()+1)+'s';
    return ret1+value;
}

string EnValues::IntToString(int value)
{
    string ret="";
    unsigned char ures;
    for (int i = 0; i <= 1; i++)
    {
        ures = value % 256;
        value /= 256;
        ret+=ures;
    }
    reverse(ret.begin(),ret.end());
    return ret;
}
/*
string MyInt::getString(any value){
    int ertek = any_cast<int>(value);
    string ret2= to_string(ertek);
    string ret1=IntToString(ret2.size()+1)+'i';
    return ret1+ret2;
}

string MyFloat::getString(any value){
    float ertek = any_cast<float>(value);
    string ret2= to_string(ertek);
    string ret1=IntToString(ret2.size()+1)+'f';
    return ret1+ret2;
}

string MyDouble::getString(any value){
    double ertek = any_cast<double>(value);
    string ret2= to_string(ertek);
    string ret1=IntToString(ret2.size()+1)+'d';
    return ret1+ret2;
}

string MyChar::getString(any value){
    char ertek = any_cast<char>(value);
    string ret1=IntToString(2)+'c'+ertek;
    return ret1;
}

string MyString::getString(any value){
    string ret2 = any_cast<const char*>(value);
    string ret1=IntToString(ret2.size()+1)+'s';
    return ret1+ret2;
}

string MyBool::getString(any value){
    bool ertek = any_cast<bool>(value);
    string ret2= to_string(ertek);
    string ret1=IntToString(ret2.size()+1)+'b';
    return ret1+ret2;
}

string MyIntP::getString(any value){
    MyIntpS ertek = any_cast<MyIntpS>(value);
    string ret2 = "I";//tipus
    ret2 += IntToString(ertek.size);//hany elem van osszesen
    for(int i=0;i<ertek.size;i++){
        string tmp = to_string(ertek.ertek[i]);
        ret2+=(IntToString(tmp.size()) + tmp);
    }
    string ret1 = IntToString(ret2.size());
    return ret1+ret2;
}

string MyFloatP::getString(any value){
    MyFloatpS ertek = any_cast<MyFloatpS>(value);
    string ret2 = "F";//tipus
    ret2 += IntToString(ertek.size);//hany elem van osszesen
    for(int i=0;i<ertek.size;i++){
        string tmp = to_string(ertek.ertek[i]);
        ret2+=(IntToString(tmp.size()) + tmp);
    }
    string ret1 = IntToString(ret2.size());
    return ret1+ret2;
}
string MyDoubleP::getString(any value){
    MyDoublepS ertek = any_cast<MyDoublepS>(value);
    string ret2 = "D";//tipus
    ret2 += IntToString(ertek.size);//hany elem van osszesen
    for(int i=0;i<ertek.size;i++){
        string tmp = to_string(ertek.ertek[i]);
        ret2+=(IntToString(tmp.size()) + tmp);
    }
    string ret1 = IntToString(ret2.size());
    return ret1+ret2;
}
string MyCharP::getString(any value){
    MyCharpS ertek = any_cast<MyCharpS>(value);
    string ret2 = "C";//tipus
    ret2 += IntToString(ertek.size);//hany elem van osszesen
    for(int i=0;i<ertek.size;i++){
        char tmp = ertek.ertek[i];
        ret2+=(IntToString(1) + tmp);
    }
    string ret1 = IntToString(ret2.size());
    return ret1+ret2;
}
string MyStringP::getString(any value){
    MyStringpS ertek = any_cast<MyStringpS>(value);
    string ret2 = "S";//tipus
    ret2 += IntToString(ertek.size);//hany elem van osszesen
    for(int i=0;i<ertek.size;i++){
        string tmp = ertek.ertek[i];
        ret2+=(IntToString(tmp.size()) + tmp);
    }
    string ret1 = IntToString(ret2.size());
    return ret1+ret2;
}
string MyBoolP::getString(any value){
    MyBoolpS ertek = any_cast<MyBoolpS>(value);
    string ret2 = "I";//tipus
    ret2 += IntToString(ertek.size);//hany elem van osszesen
    for(int i=0;i<ertek.size;i++){
        string tmp = to_string(ertek.ertek[i]);
        ret2+=(IntToString(tmp.size()) + tmp);
    }
    string ret1 = IntToString(ret2.size());
    return ret1+ret2;
}
*/
