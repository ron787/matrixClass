//
// Created by mailr on 20/11/2023.
//

#ifndef HW3_2020_INTMATRIX_H
#define HW3_2020_INTMATRIX_H

#include "Auxilaries.h"

namespace mtm
{
    class IntMatrix
    {
    public:
        explicit IntMatrix(const mtm::Dimensions& dims, int initialValue = DEFAULT_INITIAL_VALUE);

        IntMatrix(const IntMatrix& other);

        IntMatrix& operator=(const IntMatrix& other);

        ~IntMatrix();

        static IntMatrix Identity(int size);

        int getHeight() const;

        int getWidth() const;

        int getSize() const;

        static IntMatrix transpose(const IntMatrix& matrix);

        IntMatrix operator+(const IntMatrix& matrix) const;

        IntMatrix operator+(int value) const;

        IntMatrix& operator+=(const IntMatrix& matrix);

        IntMatrix& operator+=(int value);

        IntMatrix operator-() const;

        IntMatrix operator-(const IntMatrix& matrix) const;

        friend std::ostream& operator<<(std::ostream& os, const IntMatrix& matrix);

        int operator()(int row, int col) const;

        int& operator()(int row, int col);

        static IntMatrix logicOperation(int value, const IntMatrix& matrix, bool(*compare)(int num1, int num2));

        IntMatrix operator<(int value) const;

        IntMatrix operator>(int value) const;

        IntMatrix operator>=(int value) const;

        IntMatrix operator<=(int value) const;

        IntMatrix operator==(int value) const;

        IntMatrix operator!=(int value) const;

        class Iterator;

        Iterator begin();

        Iterator end();

        class ConstIterator;

        ConstIterator begin() const;

        ConstIterator end() const;


    private:
        Dimensions m_dims;
        int* m_elements;

        static const int DEFAULT_INITIAL_VALUE = 0;

    };

    IntMatrix operator+(int value, const IntMatrix& matrix);

    bool all(const IntMatrix& matrix);

    bool any(const IntMatrix& matrix);

    class IntMatrix::Iterator
    {
    public:
        int& operator*() const;

        Iterator& operator++();

        Iterator operator++(int);

        bool operator==(const Iterator& other) const;

        bool operator!=(const Iterator& other) const;

        Iterator(const Iterator& it) = default;

        Iterator& operator=(const Iterator& it) = default;

        ~Iterator() = default;

    private:
        IntMatrix* m_matrix;
        int m_index;

        Iterator(IntMatrix* matrix, int index);

        friend class IntMatrix;
    };

    class IntMatrix::ConstIterator
    {
    public:
        int operator*() const;

        ConstIterator& operator++();

        ConstIterator operator++(int);

        bool operator==(const ConstIterator& other) const;

        bool operator!=(const ConstIterator& other) const;

        ConstIterator(const ConstIterator& it) = default;

        ConstIterator& operator=(const ConstIterator& it) = default;

        ~ConstIterator() = default;

    private:
        const IntMatrix* m_matrix;
        int m_index;

        ConstIterator(const IntMatrix* matrix, int index);

        friend class IntMatrix;
    };


}


#endif //HW3_2020_INTMATRIX_H
