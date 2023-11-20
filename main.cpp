#include <iostream>
#include <vector>
#include "IntMatrix.h"

using namespace mtm;


int main()
{
    IntMatrix m1({2,3});

    m1(0,0) = 5;
    m1(0,1) = 1;
    m1(0,2) = 2;

    m1(1,0) = 4;
    m1(1,1) = 3;
    m1(1,2) = 6;

    IntMatrix m2 =  m1 < 2;

    std::cout << m2;



    return 0;
}






