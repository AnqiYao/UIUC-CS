// Your code here! :)
#include <iostream>
#include "student.h"

using namespace std;

void graduate(student* &other){
int grade = other->getGrade();
grade+=1;
other->setGrade(grade);
}


int main(){
student *a = new student("Sally",5);
cout<<a->getName()<<" is in grade "<<a->getGrade()<< endl;
graduate(a);
cout<<a->getName()<<" is in grade "<<a->getGrade()<< endl;
}

