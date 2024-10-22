#ifndef MATRIXCPP_MATRIXCALC_HPP
#define MATRIXCPP_MATRIXCALC_HPP


#include "matrix.h"
#include <algorithm>


// 加算
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

// 減算
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

// 乗算
template<typename Type>
template<typename Type_, typename execPolicy_>
inline Matrix<Type>::MatrixType<Type_> Matrix<Type>::mul_(const MatrixType<Type_>& argMatrix1, const MatrixType<Type_>& argMatrix2)
{
    //  それぞれの 列 と 行 が一緒でなければならない。
    if (this->cols_(argMatrix1) != this->rows_(argMatrix2))
        throw std::invalid_argument("The number of columns in data1 must be the same as the number of rows in data2.");

    const size_t crSize = this->cols_(argMatrix1); // 乗算する行列は各列と行が等しい

    // 出力サイズ
    Size resultSize = {this->rows_(argMatrix1),this->cols_(argMatrix2)};

    // 結果格納用
    MatrixType<Type_> result;
    result.resize(resultSize.first,RowType<Type_>(resultSize.second,0)); // 出力サイズ指定

    // pos(行,列) の値を求める。
    auto calcLambda = [&crSize,&argMatrix1,&argMatrix2](const Size& pos) {
        Type_ resultMatrix = 0; // 結果

        for (size_t i = 0; i < crSize; i++)
            resultMatrix += argMatrix1[pos.first][i] * argMatrix2[i][pos.second]; // 各列要素と行要素を乗算したものを加算する。

        return resultMatrix;
    };

    // Indeces
    std::vector<size_t> rowIndices(resultSize.first),colIndices(resultSize.second);

    // 0 ~
    std::iota(rowIndices.begin(), rowIndices.end(), 0);
    std::iota(colIndices.begin(), colIndices.end(), 0);
    
    // 各行要素毎の結果を格納する。
    // 行毎
    std::for_each(execPolicy_(), rowIndices.begin(), rowIndices.end(), [&result, &calcLambda, &colIndices](size_t rowIndex) {std::for_each(execPolicy_(), colIndices.begin(), colIndices.end(), [&result, &calcLambda, rowIndex](size_t colIndex) {result[rowIndex][colIndex] = calcLambda({rowIndex,colIndex}); }); });

    return result;
}

// アダマール積
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

// アダマール除算
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

// 各要素の演算を行う
template<typename Type>
template<typename Type_, typename calcType_, typename execPolicy_>
inline void Matrix<Type>::calcMatrix_(
    MatrixType<Type_>&       argResult,
    const MatrixType<Type_>& argSource
)
{
    // サイズが同じでなければならない。
    if (!this->areSameSize_(argResult, argSource))
        throw std::invalid_argument("The number of rows and columns of data1 and data2 must be equal.");

    // iterator
    typename MatrixType<Type_>::iterator itr = argResult.begin();

    // begin ~ end まで
    while (itr != argResult.end()) {
        RowType<Type_>& resultRow = *itr;

        // index を求める
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

// スカラの計算をさせる。
template<typename Type>
template<typename Type_, typename calcType_, typename execPolicy_>
inline void Matrix<Type>::scalarCalc_(
    MatrixType<Type_>& argResult,
    const Type_&       argSource
)
{
    // 1 行にたいして
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
    this->matrix_=this->mul_<Type, execPolicy>(this->matrix_, argOther.matrix_);

    return *this;
}

template<typename Type>
template<typename execPolicy>
inline Matrix<Type>& Matrix<Type>::scalarMul(const Type& argOther, execPolicy)
{
    this->scalarCalc_<Type,std::multiplies<Type>,execPolicy>(this->matrix_, argOther);

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
