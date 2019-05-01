#ifndef _FOOD_H
#define _FOOD_H
#include "food.h"
#include <iostream>
#include <string>
using namespace std;

class Food {
  private:
    string name;
    int quantity;
  public:
    Food();
    void setName(string newName);
    void setQuantity(int newQuantity);
    string getName();
    int getQuantity() const;
    bool operator > (Food &a);
    template <class T> T more( T &a, T &b);
    void increaseQuantity(Food * food);
};

#endif
