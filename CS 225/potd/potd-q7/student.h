// Your code here! 
#ifndef student_h 
#define student_h

#include <string>
#include "student.h"

using namespace std;


class student{
public:

student();
student(string a,int b);
void setName(string a);
void setGrade(int b);
string getName();
int getGrade();


private:
string name;
int grade;

};

#endif


