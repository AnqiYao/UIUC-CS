// pet.cpp
#include <iostream>
#include "pet.h"
#include "animal.h"

using namespace std;

pet::pet() {
setType("cat");
setFood("fish");
name="Fluffy";
owner_name="Cinda";}


pet::pet(string newtype,string newfood,string newname,string ownername){
setType(newtype);
setFood(newfood);
name=newname;
owner_name=ownername;
}

string pet::getName(){ return name;}


string pet::getOwnerName()  { return owner_name;}


void pet::setName(string otherName){ name=otherName;}


void pet::setOwnerName(string otherOwnerName){ owner_name=otherOwnerName;}


void pet::print(){   cout<<"My name is "<<name<<"."<<endl;} 
