//
// Created by mailr on 20/11/2023.
//

#ifndef HW3_2020_MATRIX_H
#define HW3_2020_MATRIX_H

#include "Auxilaries.h"
#include <assert.h>



namespace mtm
{
    template<class T>
    class Matrix
    {
    public:
        explicit Matrix(const mtm::Dimensions& dims, const T& initialValue = T());

        Matrix(const Matrix& other);

        Matrix& operator=(const Matrix& other);

        ~Matrix();

        static Matrix Diagonal(int size, const T& value);

        int getHeight() const;

        int getWidth() const;

        int getSize() const;

        static Matrix transpose(const Matrix& matrix);

        Matrix operator+(const Matrix& matrix) const;

        Matrix operator+(const T& value) const;

        Matrix& operator+=(const Matrix& matrix);

        Matrix& operator+=(const T& value);

        Matrix operator-() const;

        Matrix operator-(const Matrix& matrix) const;

        template<class S>
        friend std::ostream& operator<<(std::ostream& os, const Matrix<S>& matrix);

        const T& operator()(int row, int col) const;

        T& operator()(int row, int col);


        template<class S>
        friend Matrix<bool> logicOperation(const S& value, const Matrix<S>& matrix, bool(*compare)(int num1, int num2));

        Matrix<bool> operator<(int value) const;

        Matrix<bool> operator>(int value) const;

        Matrix<bool> operator>=(int value) const;

        Matrix<bool> operator<=(int value) const;

        Matrix<bool> operator==(int value) const;

        Matrix<bool> operator!=(int value) const;

        class Iterator;

        Iterator begin();

        Iterator end();

        class ConstIterator;

        ConstIterator begin() const;

        ConstIterator end() const;

        class DimensionMismatch;

        class AccessIllegalElement;

        class IllegalInitialization;

        Matrix apply(T(*func)(T element));


    private:
        Dimensions m_dims;
        T* m_elements;
    };

    template<class T>
    Matrix<T> Matrix<T>::apply(T(*func)(T element))
    {
        Matrix result = *this;
        for(int i = 0; i < result.getSize(); i++)
        {
            result.m_elements[i] = func(result.m_elements[i]);
        }

        return result;
    }


    template<class T>
    Matrix<T> operator+(T value, const Matrix<T>& matrix);

    template<class T>
    bool all(const Matrix<T>& matrix);

    template<class T>
    bool any(const Matrix<T>& matrix);

    template<class T>
    class Matrix<T>::Iterator
    {
    public:
        T& operator*() const;

        Iterator& operator++();

        Iterator operator++(int);

        bool operator==(const Iterator& other) const;

        bool operator!=(const Iterator& other) const;

        Iterator(const Iterator& it) = default;

        Iterator& operator=(const Iterator& it) = default;

        ~Iterator() = default;

    private:
        Matrix* m_matrix;
        int m_index;

        Iterator(Matrix* matrix, int index);

        friend class Matrix;
    };

    template<class T>
    class Matrix<T>::ConstIterator
    {
    public:
        const T& operator*() const;

        ConstIterator& operator++();

        ConstIterator operator++(int);

        bool operator==(const ConstIterator& other) const;

        bool operator!=(const ConstIterator& other) const;

        ConstIterator(const ConstIterator& it) = default;

        ConstIterator& operator=(const ConstIterator& it) = default;

        ~ConstIterator() = default;

    private:
        const Matrix* m_matrix;
        int m_index;

        ConstIterator(const Matrix* matrix, int index);

        friend class Matrix;
    };

    template<class T>
    class Matrix<T>::IllegalInitialization : public std::runtime_error
    {
    public:
        IllegalInitialization() : std::runtime_error("Mtm matrix error: Illegal initialization values") {}
    };

    template<class T>
    class Matrix<T>::AccessIllegalElement : public std::runtime_error
    {
    public:
        AccessIllegalElement() : std::runtime_error("Mtm matrix error: An attempt to access an illegal element") {}
    };

    template<class T>
    class Matrix<T>::DimensionMismatch : public std::runtime_error
    {
    public:
        DimensionMismatch(Dimensions dim1, Dimensions dim2) : std::runtime_error("Mtm matrix error: Dimension mismatch: ("
        + std::to_string(dim1.getRow()) + ", " + std::to_string(dim1.getCol()) + ") (" + std::to_string(dim2.getRow())
        + ", " + std::to_string(dim2.getCol()) + ")") {}
    };



    // IMPLEMENTING FUNCTIONS


    template<class T>
    Matrix<T>::Matrix(const Dimensions& dims, const T& initialValue) : m_dims(dims)
    {

        if (m_dims.getCol() <= 0 || m_dims.getRow() <= 0)
        {
            throw Matrix::IllegalInitialization();
        }

        m_elements = new T[dims.getRow() * dims.getCol()];

        for (int i = 0; i < m_dims.getRow() * m_dims.getCol(); i++)
        {
            m_elements[i] = initialValue;
        }
    }

    template<class T>
    Matrix<T>::Matrix(const Matrix& other) : m_dims(other.m_dims),
                                          m_elements(new T[other.m_dims.getRow() * other.m_dims.getCol()])
    {
        for (int i = 0; i < m_dims.getRow() * m_dims.getCol(); i++)
        {
            m_elements[i] = other.m_elements[i];
        }
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix& other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] m_elements;
        m_dims = other.m_dims;
        m_elements = new T[m_dims.getRow() * m_dims.getCol()];
        for (int i = 0; i < m_dims.getRow() * m_dims.getCol(); i++)
        {
            m_elements[i] = other.m_elements[i];
        }

        return *this;
    }

    template<class T>
    Matrix<T>::~Matrix()
    {
        delete[] m_elements;
    }

    template<class T>
    Matrix<T> Matrix<T>::Diagonal(int size, const T& value)
    {

        Matrix diagonalMatrix({size, size});
        for (int i = 0; i < size; i++)
        {
            diagonalMatrix(i, i) = value;
        }

        return diagonalMatrix;
    }

    template<class T>
    int Matrix<T>::getHeight() const
    {
        return m_dims.getRow();
    }

    template<class T>
    int Matrix<T>::getWidth() const
    {
        return m_dims.getCol();
    }

    template<class T>
    int Matrix<T>::getSize() const
    {
        return getHeight() * getWidth();
    }

    template<class T>
    Matrix<T> Matrix<T>::transpose(const Matrix& matrix)
    {
        Matrix transposedMatrix({matrix.getWidth(), matrix.getHeight()});
        for (int i = 0; i < transposedMatrix.getHeight(); i++)
        {
            for (int j = 0; j < transposedMatrix.getWidth(); j++)
            {
                transposedMatrix(i, j) = matrix(j, i);
            }
        }

        return transposedMatrix;

    }

    template<class T>
    Matrix<T>& Matrix<T>::operator+=(const Matrix& matrix)
    {
        if (m_dims != matrix.m_dims)
        {
            throw Matrix::DimensionMismatch(m_dims, matrix.m_dims);
        }

        for (int i = 0; i < getSize(); i++)
        {
            m_elements[i] += matrix.m_elements[i];
        }

        return *this;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator+(const Matrix& matrix) const
    {
        return Matrix(*this) += matrix;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator+(const T& value) const
    {
        return (*this) + Matrix(m_dims, value);
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator+=(const T& value)
    {
        Matrix valueMatrix(m_dims, value);
        this->operator+=(valueMatrix);
        return *this;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator-() const
    {
        Matrix minusMatrix(*this);

        for (int i = 0; i < minusMatrix.getSize(); i++)
        {
            minusMatrix.m_elements[i] = -minusMatrix.m_elements[i];
        }

        return minusMatrix;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator-(const Matrix& matrix) const
    {
        Matrix result(*this);
        result += -(matrix);
        return result;
    }

    template<class S>
    std::ostream& operator<<(std::ostream& os, const Matrix<S>& matrix) //TODO: fix
    {
        printMatrix(os, matrix.begin(), matrix.end(), matrix.getWidth());
        return os;
    }

    template<class T>
    const T& Matrix<T>::operator()(int row, int col) const
    {
        if (row < 0 || row >= getHeight() || col < 0 || col >= getWidth())
        {
            throw Matrix::AccessIllegalElement();
        }

        return m_elements[getWidth() * row + col];
    }

    template<class T>
    T& Matrix<T>::operator()(int row, int col)
    {
        if (row < 0 || row >= getHeight() || col < 0 || col >= getWidth())
        {
            throw Matrix::AccessIllegalElement();
        }

        return m_elements[getWidth() * row + col];
    }




    template<class S>
    Matrix<bool> logicOperation(const S& value, const Matrix<S>& matrix, bool(* compare)(int num1, int num2))
    {
        Matrix<bool> result(matrix.m_dims);

        for (int i = 0; i < matrix.getSize(); i++)
        {
            if (compare(matrix.m_elements[i], value)) result.m_elements[i] = true;
        }

        return result;
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator<(int value) const
    {
        return logicOperation(value, *this, [](int num1, int num2)
        { return num1 < num2; });
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator>(int value) const
    {
        return logicOperation(value, *this, [](int num1, int num2)
        { return num1 > num2; });
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator>=(int value) const
    {
        return logicOperation(value, *this, [](int num1, int num2)
        { return num1 >= num2; });
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator<=(int value) const
    {
        return logicOperation(value, *this, [](int num1, int num2)
        { return num1 <= num2; });
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator==(int value) const
    {
        return logicOperation(value, *this, [](int num1, int num2)
        { return num1 == num2; });
    }

    template<class T>
    Matrix<bool> Matrix<T>::operator!=(int value) const
    {
        return logicOperation(value, *this, [](int num1, int num2)
        { return num1 != num2; });
    }

    template<class T>
    Matrix<T> operator+(T value, const Matrix<T>& matrix)
    {
        return Matrix<T>({matrix.getHeight(), matrix.getWidth()}, value) + matrix;
    }

    template<class T>
    bool all(const Matrix<T>& matrix)
    {
        for (int i = 0; i < matrix.getHeight(); i++)
        {
            for (int j = 0; j < matrix.getWidth(); j++)
            {
                if (matrix(i, j) == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }

    template<class T>
    bool any(const Matrix<T>& matrix)
    {
        for (int i = 0; i < matrix.getHeight(); i++)
        {
            for (int j = 0; j < matrix.getWidth(); j++)
            {
                if (matrix(i, j) != 0)
                {
                    return true;
                }
            }
        }
        return false;
    }

    template<class T>
    typename Matrix<T>::Iterator Matrix<T>::begin()
    {
        return {this, 0};
    }

    template<class T>
    typename Matrix<T>::Iterator Matrix<T>::end()
    {
        return {this, getSize()};
    }

    template<class T>
    typename Matrix<T>::ConstIterator Matrix<T>::begin() const
    {
        return {this, 0};
    }

    template<class T>
    typename Matrix<T>::ConstIterator Matrix<T>::end() const
    {
        return {this, getSize()};
    }

// Iterator

    template<class T>
    T& Matrix<T>::Iterator::operator*() const
    {
        return m_matrix->m_elements[m_index];
    }

    template<class T>
    typename Matrix<T>::Iterator& Matrix<T>::Iterator::operator++()
    {
        m_index++;
        return *this;
    }

    template<class T>
    typename Matrix<T>::Iterator Matrix<T>::Iterator::operator++(int)
    {
        Iterator it = *this;
        ++(*this);
        return it;
    }

    template<class T>
    bool Matrix<T>::Iterator::operator==(const Iterator& other) const
    {
        assert(m_matrix == other.m_matrix);
        return m_index == other.m_index;
    }

    template<class T>
    bool Matrix<T>::Iterator::operator!=(const Iterator& other) const
    {
        return !(*this == other);
    }

    template<class T>
    Matrix<T>::Iterator::Iterator(Matrix* matrix, int index) : m_matrix(matrix), m_index(index)
    {}

// const Iterator

    template<class T>
    const T& Matrix<T>::ConstIterator::operator*() const
    {
        return m_matrix->m_elements[m_index];
    }

    template<class T>
    typename Matrix<T>::ConstIterator& Matrix<T>::ConstIterator::operator++()
    {
        m_index++;
        return *this;
    }

    template<class T>
    typename Matrix<T>::ConstIterator Matrix<T>::ConstIterator::operator++(int)
    {
        ConstIterator it = *this;
        ++(*this);
        return it;
    }

    template<class T>
    bool Matrix<T>::ConstIterator::operator==(const ConstIterator& other) const
    {
        assert(m_matrix == other.m_matrix);
        return m_index == other.m_index;
    }

    template<class T>
    bool Matrix<T>::ConstIterator::operator!=(const ConstIterator& other) const
    {
        return !(*this == other);
    }

    template<class T>
    Matrix<T>::ConstIterator::ConstIterator(const Matrix* matrix, int index) : m_matrix(matrix), m_index(index)
    {}


}


#endif //HW3_2020_MATRIX_H
