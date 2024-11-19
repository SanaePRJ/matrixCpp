#ifndef MATRIXCPP_MATRIXUTILS_HPP
#define MATRIXCPP_MATRIXUTILS_HPP


#include "matrix.h"
#include <execution>


template<typename Type>
template<typename CopyType_,typename execPolicy>
inline void Matrix<Type>::copyMatrix_(MatrixType<CopyType_>& argCopy,const MatrixType<CopyType_>& argOrigin)
{
    argCopy.resize(argOrigin.size(), RowType<CopyType_>(argOrigin.at(0).size()));
    std::transform(execPolicy(), argOrigin.begin(), argOrigin.end(), argCopy.begin(), [](const RowType<CopyType_>& argRow) { return argRow; });
}

template<typename Type>
template<typename Type_>
inline size_t Matrix<Type>::rows_(const MatrixType<Type_>& argMatrix) const noexcept
{
    return argMatrix.size();
}

template<typename Type>
template<typename Type_>
inline size_t Matrix<Type>::cols_(const MatrixType<Type_>& argMatrix) const noexcept
{
    if (this->rows_(argMatrix) == 0)
        return 0;

    return argMatrix.at(0).size();
}

template<typename Type>
template<typename Type1_, typename Type2_>
inline bool Matrix<Type>::areSameSize_(const MatrixType<Type1_>& argMatrix1, const MatrixType<Type2_>& argMatrix2) const noexcept
{
    if (
        this->rows_(argMatrix1) == this->rows_(argMatrix2)
        &&
        this->cols_(argMatrix1) == this->cols_(argMatrix2)
        )
        return true;

    return false;
}

template<typename Type>
template<typename Type_>
inline void Matrix<Type>::validateMatrix_(const MatrixType<Type_>& argCheckMatrix_)
{
    if (this->rows_(argCheckMatrix_) == 0)
        return;

    auto   itr       = argCheckMatrix_.begin();
    size_t firstSize = argCheckMatrix_.at(0).size();

    itr++; // 次へ進める。

    while (itr != argCheckMatrix_.end()) {
        if (itr->size() != firstSize)
            throw std::exception("invalid matrix.");

        itr++;
    }

    return;
}

template<typename Type>
inline const size_t Matrix<Type>::rows()
{
    return this->rows_(this->matrix_);
}

template<typename Type>
inline const size_t Matrix<Type>::cols()
{
    return this->cols_(this->matrix_);
}

template<typename Type>
inline std::vector<std::reference_wrapper<Type>> Matrix<Type>::rowRef(const size_t& argPos)
{
    std::vector<std::reference_wrapper<Type>> resultRef(this->cols());

    for (auto& elem : this->matrix_[argPos])
        resultRef.push_back(elem);

    return resultRef;
}

template<typename Type>
inline std::vector<std::reference_wrapper<Type>> Matrix<Type>::colRef(const size_t& argPos)
{
    std::vector<std::reference_wrapper<Type>> resultRef(this->rows());

    for (auto& elem : this->matrix_)
        resultRef.push_back(elem);

}

template<typename Type>
template<typename execPolicy>
inline Matrix<Type>& Matrix<Type>::forEach(std::function<Type()> argFunc, execPolicy)
{
    std::for_each(execPolicy(), this->matrix_.begin(), this->matrix_.end(), [&](Matrix<Type>::RowType<Type>& row) {
        std::for_each(execPolicy(), row.begin(), row.end(), [&](Type& elem) {
            elem = argFunc();
            });
        });
    return *this;
}



#endif
