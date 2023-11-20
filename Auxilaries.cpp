//
// Created by mailr on 20/11/2023.
//

#include "Auxilaries.h"

mtm::Dimensions::Dimensions(int row, int col) : m_row(row), m_col(col)
{}

std::string mtm::Dimensions::toString() const
{
    return "(" + std::to_string(m_row) + ", " + std::to_string(m_col) + ")";
}

bool mtm::Dimensions::operator==(const Dimensions& other) const
{
    return (m_row == other.m_row) && (m_col == other.m_col);
}

bool mtm::Dimensions::operator!=(const Dimensions& other) const
{
    return !(*this == other);
}

int mtm::Dimensions::getRow() const
{
    return m_row;
}

int mtm::Dimensions::getCol() const
{
    return m_col;
}

std::string mtm::printMatrix(const int* matrix, const Dimensions& dim)
{
    std::string matrix_str;
    int col_length = dim.getCol();
    for (int i = 0; i < dim.getRow(); i++)
    {
        for (int j = 0; j < col_length; j++)
        {
            matrix_str += std::to_string(*(matrix + col_length * i + j)) + " ";
        }

        matrix_str += "\n";
    }
    matrix_str += "\n";
    return matrix_str;
}