#pragma once
#include <string>
#include "blok.h"
using namespace std;
class Fruits : public blok{
private:
    float x, z;
public:
  
    float get_x();

    float get_z();

    void New();
    void check();
    void print();
} apple;

