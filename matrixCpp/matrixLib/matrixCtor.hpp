#ifndef MATRIXCPP_MATRIXCTOR_HPP
#define MATRIXCPP_MATRIXCTOR_HPP


#include "matrix.h"
#include <execution>
#include <utility>
#include <algorithm>


template<typename Type>
inline Matrix<Type>::Matrix
(
    const Matrix<Type>::MatrixInitType<>& argMatrixInit
)
    : matrix_(argMatrixInit.begin(), argMatrixInit.end())
{}

template<typename Type>
inline Matrix<Type>::Matrix
(
    const Matrix<Type>::Size& argSize
)
{
    matrix_.resize(argSize.first,RowType<Type>(argSize.second,0)); // 指定されたサイズを確保する。
}

template<typename Type>
inline Matrix<Type>::Matrix
(
    const Matrix<Type>& copyMatrix
)
{
    copyMatrix_(matrix_, copyMatrix.matrix_); // 行列のコピー
}

template<typename Type>
inline Matrix<Type>::Matrix
(
    Matrix<Type>&& otherMatrix
)
    noexcept
    : matrix_(std::move(otherMatrix.matrix_))
{
    // 元のオブジェクトのリソースを無効化
    otherMatrix.matrix_.clear();
}


#endif
