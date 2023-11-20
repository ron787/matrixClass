#include <iostream>
#include <vector>
#include "Matrix.h"

using namespace mtm;

int Square(int num)
{
    return num * num;
}

int main()
{

//    Matrix<std::string> m1({2, 3}, "Hello");

      Matrix<int> m1 = Matrix<int>::Diagonal(3,5);

      std::cout << m1;

      Matrix<int> m2 = m1.apply(Square);

      std::cout << m2;


    return 0;
}






