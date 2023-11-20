#include <iostream>
#include <vector>
#include "IntMatrix.h"

using namespace mtm;


int main()
{

    try
    {
        Dimensions dim(2, 5);
        IntMatrix mat_1(dim);
        std::cout << mat_1(5,6) << std::endl;
    }
    catch (const mtm::IntMatrix::DimensionMismatch& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}






