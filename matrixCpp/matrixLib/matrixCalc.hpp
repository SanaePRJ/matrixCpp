#ifndef MATRIXCPP_MATRIXCALC_HPP
#define MATRIXCPP_MATRIXCALC_HPP


#include "matrix.h"
#include <algorithm>


template<typename Type>
template<typename Type_, typename execPolicy_>
inline void Matrix<Type>::add_
(
    MatrixType<Type_>&       argResult,
    const MatrixType<Type_>& argSource
)
{
    this->calcMatrix_<Type_,std::plus<Type_>,execPolicy_>(argResult,argSource);
    return;
}

template<typename Type>
template<typename Type_, typename execPolicy_>
inline void Matrix<Type>::sub_
(
    MatrixType<Type_>&       argResult,
    const MatrixType<Type_>& argSource
)
{
    this->calcMatrix_<Type_, std::minus<Type_>, execPolicy_>(argResult, argSource);
    return;
}

template<typename Type>
template<typename Type_, typename execPolicy_>
inline void Matrix<Type>::hadamardMul_
(
    MatrixType<Type_>&       argResult,
    const MatrixType<Type_>& argSource
)
{
    this->calcMatrix_<Type_, std::multiplies<Type_>, execPolicy_>(argResult, argSource);
    return;
}

template<typename Type>
template<typename Type_, typename execPolicy_>
inline void Matrix<Type>::hadamardDiv_
(
    MatrixType<Type_>&       argResult,
    const MatrixType<Type_>& argSource
)
{
    this->calcMatrix_<Type_, std::divides<Type_>, execPolicy_>(argResult, argSource);
    return;
}

template<typename Type>
template<typename Type_, typename calcType_, typename execPolicy_>
inline void Matrix<Type>::calcMatrix_(
    MatrixType<Type_>&       argResult,
    const MatrixType<Type_>& argSource
)
{
    if (!this->areSameSize_(argResult, argSource))
        throw std::invalid_argument("The number of rows and columns of data1 and data2 must be equal.");

    typename MatrixType<Type_>::iterator itr = argResult.begin();

    while (itr != argResult.end()) {
        RowType<Type_>& resultRow = *itr;
        size_t rowIndex = std::distance(argResult.begin(),itr);

        // 各要素
        std::transform(execPolicy_(), resultRow.begin(), resultRow.end(), argSource.at(rowIndex).cbegin(), resultRow.begin(),
            [&](Type_& resultElem, const Type_& sourceElem) {
                return calcType_()(resultElem, sourceElem);
            }
        );

        itr++;
    }

    return;
}

template<typename Type>
template<typename Type_, typename calcType_, typename execPolicy_>
inline void Matrix<Type>::scalarCalc_(
    MatrixType<Type_>& argResult,
    const Type_&       argSource
)
{
    auto processRow = [&](RowType<Type_>& resultRow) {
        std::for_each(execPolicy_(), resultRow.begin(), resultRow.end(),
            [&](Type_& resultElem){
                resultElem = calcType_()(resultElem, argSource);
            }
        );
    };

    // 行ごとに並列で計算
    std::for_each(execPolicy_(), argResult.begin(), argResult.end(), processRow);

    return;
}

template<typename Type>
template<typename execPolicy>
inline Matrix<Type>& Matrix<Type>::add(const Matrix<Type>& argOther,execPolicy)
{
    this->add_<Type, execPolicy>(this->matrix_,argOther.matrix_);

    return *this;
}

template<typename Type>
template<typename execPolicy>
inline Matrix<Type>& Matrix<Type>::sub(const Matrix<Type>& argOther, execPolicy)
{
    this->sub_<Type, execPolicy>(this->matrix_, argOther.matrix_);

    return *this;
}

template<typename Type>
template<typename execPolicy>
inline Matrix<Type>& Matrix<Type>::mul(const Matrix<Type>& argOther, execPolicy)
{
    this->mul_<Type, execPolicy>(this->matrix_, argOther.matrix_);

    return *this;
}

template<typename Type>
template<typename execPolicy>
inline Matrix<Type>& Matrix<Type>::scalarMul(const Type& argOther, execPolicy)
{
    this->scalarCalc_<Type,std::multiplies,execPolicy>(this->matrix_, argOther.matrix_);

    return *this;
}

template<typename Type>
template<typename execPolicy>
inline Matrix<Type>& Matrix<Type>::hadamardMul(const Matrix<Type>& argOther, execPolicy)
{
    this->hadamardMul_<Type, execPolicy>(this->matrix_, argOther.matrix_);

    return *this;
}

template<typename Type>
template<typename execPolicy>
inline Matrix<Type>& Matrix<Type>::hadamardDiv(const Matrix<Type>& argOther, execPolicy)
{
    this->hadamardDiv_<Type, execPolicy>(this->matrix_, argOther.matrix_);

    return *this;
}

template<typename Type>
template<typename calcType, typename execPolicy>
inline Matrix<Type>& Matrix<Type>::scalarCalc(const Matrix<Type>& argOther, execPolicy)
{
    this->scalarCalc_<Type, calcType,execPolicy>(this->matrix_, argOther);

    return *this;
}


#endif
