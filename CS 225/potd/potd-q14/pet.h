// pet.h
#ifndef PET_H
#define PET_H
#include "pet.h"
#include "animal.h"


class pet:public animal{

public:
pet();
pet(string newtype,string newfood,string newname,string ownername);
string getName();
string getOwnerName();
void setName(string otherName);
void setOwnerName(string otherOwnerName);
void print();

private:
string name;
string owner_name;
};


#endif
