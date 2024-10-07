#ifndef MATRIXCPP_MATRIXOP_HPP
#define MATRIXCPP_MATRIXOP_HPP


#include "matrix.h"
#include <algorithm>
#include <execution>


template<typename Type>
inline Matrix<Type>& Matrix<Type>::operator=(const MatrixInitType<Type>& argInitMatrix)
{
    matrix_ = {argInitMatrix.begin(),argInitMatrix.end()};

    return *this;
}

template<typename Type>
inline Matrix<Type>& Matrix<Type>::operator=(const Matrix<Type>& originMatrix)
{
    matrix_.resize(originMatrix.matrix_.size(), RowType<Type>(originMatrix.matrix_.at(0).size(), 0)); // 確保
    std::copy(std::execution::par_unseq, originMatrix.matrix_.begin(), originMatrix.matrix_.end(), matrix_.begin());

    return *this;
}

template<typename Type>
inline Matrix<Type>& Matrix<Type>::operator<<(const MatrixInitType<Type>& argInitMatrix)
{
    matrix_ = { argInitMatrix.begin(),argInitMatrix.end() };

    return *this;
}

template<typename Type>
inline Matrix<Type>& Matrix<Type>::operator<<(const Matrix<Type>& originMatrix)
{
    matrix_.resize(originMatrix.matrix_.size(), RowType<Type>(originMatrix.matrix_.at(0).size(), 0)); // 確保
    std::copy(std::execution::par_unseq, originMatrix.matrix_.begin(), originMatrix.matrix_.end(), matrix_.begin()); // コピー

    return *this;
}

template<typename Type>
inline Matrix<Type>& Matrix<Type>::operator=(Matrix<Type>&& argOther)
{
    // 同じオブジェクトでない
    if (this != &argOther) {
        matrix_ = std::move(argOther.matrix_);

        argOther.matrix_.clear(); // 使用不可
    }

    return *this;
}

template<typename Type>
inline Matrix<Type>& Matrix<Type>::operator<<(Matrix<Type>&& argOther)
{
    // 同じオブジェクトでない
    if (this != &argOther) {
        matrix_ = std::move(argOther.matrix_);

        argOther.matrix_.clear(); // 使用不可
    }

    return *this;
}

template<typename Type>
inline Matrix<Type>::RowType<Type>& Matrix<Type>::operator[](size_t argPos)
{
    if (matrix_.size() <= argPos)
        throw std::invalid_argument("Attempted to access outside range.");

    return matrix_.at(argPos);
}


#endif
