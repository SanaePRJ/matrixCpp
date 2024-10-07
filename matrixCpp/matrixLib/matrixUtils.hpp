#ifndef MATRIXCPP_MATRIXUTILS_HPP
#define MATRIXCPP_MATRIXUTILS_HPP


#include "matrix.h"
#include <execution>


template<typename Type>
template<typename copyType>
inline void Matrix<Type>::copyMatrix_(MatrixType<copyType>& argCopy,const MatrixType<copyType>& argOrigin)
{
    argCopy.resize(argOrigin.size(), RowType<copyType>(argOrigin.at(0).size()));
    std::transform(std::execution::par, argOrigin.begin(), argOrigin.end(), argCopy.begin(), [](const RowType<copyType>& argRow) { return argRow; });
}


#endif
