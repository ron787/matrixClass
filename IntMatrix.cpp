//
// Created by mailr on 20/11/2023.
//

#include "IntMatrix.h"
#include <assert.h>

mtm::IntMatrix::IntMatrix(const mtm::Dimensions& dims, int initialValue) : m_dims(dims), m_elements(new int[dims.getRow() * dims.getCol()])
{
    for (int i = 0; i < m_dims.getRow() * m_dims.getCol(); i++)
    {
        m_elements[i] = initialValue;
    }
}

mtm::IntMatrix::IntMatrix(const IntMatrix& other) : m_dims(other.m_dims), m_elements(new int[other.m_dims.getRow() * other.m_dims.getCol()])
{
    for (int i = 0; i < m_dims.getRow() * m_dims.getCol(); i++)
    {
        m_elements[i] = other.m_elements[i];
    }
}

mtm::IntMatrix& mtm::IntMatrix::operator=(const IntMatrix& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] m_elements;
    m_dims = other.m_dims;
    m_elements = new int[m_dims.getRow() * m_dims.getCol()];
    for (int i = 0; i < m_dims.getRow() * m_dims.getCol(); i++)
    {
        m_elements[i] = other.m_elements[i];
    }

    return *this;
}

mtm::IntMatrix::~IntMatrix()
{
    delete[] m_elements;
}

mtm::IntMatrix mtm::IntMatrix::Identity(int size)
{

    IntMatrix identityMatrix({size, size});
    for (int i = 0; i < size; i++)
    {
        identityMatrix(i, i) = 1;
    }

    return identityMatrix;
}

int mtm::IntMatrix::getHeight() const
{
    return m_dims.getRow();
}

int mtm::IntMatrix::getWidth() const
{
    return m_dims.getCol();
}

int mtm::IntMatrix::getSize() const
{
    return getHeight() * getWidth();
}

mtm::IntMatrix mtm::IntMatrix::transpose(const IntMatrix& matrix)
{
    IntMatrix transposedMatrix({matrix.getWidth(), matrix.getHeight()});
    for (int i = 0; i < transposedMatrix.getHeight(); i++)
    {
        for (int j = 0; j < transposedMatrix.getWidth(); j++)
        {
            transposedMatrix(i, j) = matrix(j, i);
        }
    }

    return transposedMatrix;

}

mtm::IntMatrix& mtm::IntMatrix::operator+=(const IntMatrix& matrix)
{
    for (int i = 0; i < getSize(); i++)
    {
        m_elements[i] += matrix.m_elements[i];
    }

    return *this;
}


mtm::IntMatrix mtm::IntMatrix::operator+(const IntMatrix& matrix) const
{
    return IntMatrix(*this) += matrix;
}

mtm::IntMatrix mtm::IntMatrix::operator+(int value) const
{
    return (*this) + IntMatrix(m_dims, value);
}

mtm::IntMatrix& mtm::IntMatrix::operator+=(int value)
{
    IntMatrix valueMatrix(m_dims, value);
    this->operator+=(valueMatrix);
    return *this;
}

mtm::IntMatrix mtm::IntMatrix::operator-() const
{
    IntMatrix minusMatrix(*this);

    for (int i = 0; i < minusMatrix.getSize(); i++)
    {
        minusMatrix.m_elements[i] = -minusMatrix.m_elements[i];
    }

    return minusMatrix;
}

mtm::IntMatrix mtm::IntMatrix::operator-(const IntMatrix& matrix) const
{
    IntMatrix result(*this);
    result += -(matrix);
    return result;
}

std::ostream& mtm::operator<<(std::ostream& os, const mtm::IntMatrix& matrix)
{
    os << mtm::printMatrix(matrix.m_elements, {matrix.getHeight(), matrix.getWidth()});
    return os;
}

int mtm::IntMatrix::operator()(int row, int col) const
{
    return m_elements[getWidth() * row + col];
}

int& mtm::IntMatrix::operator()(int row, int col)
{
    return m_elements[getWidth() * row + col];
}

mtm::IntMatrix mtm::IntMatrix::logicOperation(int value, const IntMatrix& matrix, bool(*compare)(int num1, int num2))
{
    IntMatrix result(matrix.m_dims);

    for (int i = 0; i < matrix.getSize(); i++)
    {
        if (compare(matrix.m_elements[i], value)) result.m_elements[i] = 1;
    }

    return result;
}

mtm::IntMatrix mtm::IntMatrix::operator<(int value) const
{
    return logicOperation(value, *this, [](int num1, int num2){return num1 < num2;});
}

mtm::IntMatrix mtm::IntMatrix::operator>(int value) const
{
    return logicOperation(value, *this, [](int num1, int num2){return num1 > num2;});
}

mtm::IntMatrix mtm::IntMatrix::operator>=(int value) const
{
    return logicOperation(value, *this, [](int num1, int num2){return num1 >= num2;});
}

mtm::IntMatrix mtm::IntMatrix::operator<=(int value) const
{
    return logicOperation(value, *this, [](int num1, int num2){return num1 <= num2;});
}

mtm::IntMatrix mtm::IntMatrix::operator==(int value) const
{
    return logicOperation(value, *this, [](int num1, int num2){return num1 == num2;});
}

mtm::IntMatrix mtm::IntMatrix::operator!=(int value) const
{
    return logicOperation(value, *this, [](int num1, int num2){return num1 != num2;});
}

mtm::IntMatrix mtm::operator+(int value, const mtm::IntMatrix& matrix)
{
    return (matrix) + mtm::IntMatrix({matrix.getHeight(), matrix.getWidth()}, value);
}

bool mtm::all(const IntMatrix& matrix)
{
    for(int i = 0; i < matrix.getHeight(); i++)
    {
        for(int j = 0; j < matrix.getWidth(); j++)
        {
            if(matrix(i,j) == 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool mtm::any(const IntMatrix& matrix)
{
    for(int i = 0; i < matrix.getHeight(); i++)
    {
        for(int j = 0; j < matrix.getWidth(); j++)
        {
            if(matrix(i,j) != 0)
            {
                return true;
            }
        }
    }
    return false;
}


mtm::IntMatrix::Iterator mtm::IntMatrix::begin()
{
    return {this, 0};
}

mtm::IntMatrix::Iterator mtm::IntMatrix::end()
{
    return {this, getSize()};
}

mtm::IntMatrix::ConstIterator mtm::IntMatrix::begin() const
{
    return {this, 0};
}

mtm::IntMatrix::ConstIterator mtm::IntMatrix::end() const
{
    return {this, getSize()};
}

// Iterator

int& mtm::IntMatrix::Iterator::operator*() const
{
    return m_matrix->m_elements[m_index];
}

mtm::IntMatrix::Iterator& mtm::IntMatrix::Iterator::operator++()
{
    m_index++;
    return *this;
}

mtm::IntMatrix::Iterator mtm::IntMatrix::Iterator::operator++(int)
{
    Iterator it = *this;
    ++(*this);
    return it;
}

bool mtm::IntMatrix::Iterator::operator==(const Iterator& other) const
{
    assert(m_matrix == other.m_matrix);
    return m_index == other.m_index;
}

bool mtm::IntMatrix::Iterator::operator!=(const Iterator& other) const
{
    return !(*this == other);
}

mtm::IntMatrix::Iterator::Iterator(IntMatrix* matrix, int index) : m_matrix(matrix), m_index(index){}

// const Iterator

int mtm::IntMatrix::ConstIterator::operator*() const
{
    return m_matrix->m_elements[m_index];
}

mtm::IntMatrix::ConstIterator& mtm::IntMatrix::ConstIterator::operator++()
{
    m_index++;
    return *this;
}

mtm::IntMatrix::ConstIterator mtm::IntMatrix::ConstIterator::operator++(int)
{
    ConstIterator it = *this;
    ++(*this);
    return it;
}

bool mtm::IntMatrix::ConstIterator::operator==(const ConstIterator& other) const
{
    assert(m_matrix == other.m_matrix);
    return m_index == other.m_index;
}

bool mtm::IntMatrix::ConstIterator::operator!=(const ConstIterator& other) const
{
    return !(*this == other);
}

mtm::IntMatrix::ConstIterator::ConstIterator(const IntMatrix* matrix, int index) : m_matrix(matrix), m_index(index){}








