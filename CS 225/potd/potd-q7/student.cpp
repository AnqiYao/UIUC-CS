// Your code here! :)
#include "student.h"
#include <iostream>
#include <string>

using namespace std;


student::student(){}

student::student(string a, int b):name(a),grade(b){}



void student::setName(string a){
 name=a;
}

void student::setGrade(int b){
grade = b;
}

string student::getName(){
return name;
}

int student::getGrade(){
return grade;
}


	
