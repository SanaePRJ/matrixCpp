#include <iostream>
#include "matrixLib/matrix"
#include <execution>

int main()
{
    //matrixCtor.hpp - demoCode
    {
        using Type = int;

        Matrix<Type> ctorNone; // 指定なし

        Matrix<Type> ctorInit =
        {
            {1,2,3},
            {4,5,6},
            {7,8,9}
        }; // 値指定

        Matrix<Type> ctorSize = Matrix<Type>::Size{3,3}; // サイズ指定

        Matrix<Type> ctorCopy = ctorInit;            // コピー
        Matrix<Type> ctorMove = std::move(ctorInit); // move
    }

    // matrixOps.hpp - demoCode
    {
        using Type = int;

        Matrix<Type> opsAssign;
        opsAssign = { {1,2,3} };

        Matrix<Type> opsCopy;
        opsCopy = opsAssign; // opsCopy << opsInit;

        Matrix<Type> opsInit;
        opsInit << Matrix<Type>::MatrixInitType<Type>{{1,2,3}};
        
        Matrix<Type> opsMove;
        opsMove << std::move(opsCopy);


        const Matrix<Type> buf = {
            {1,2,3},
            {4,5,6},
            {7,8,9}
        };

        const Matrix<Type> opsCalc = {
            {1,2,3},
            {4,5,6},
            {7,8,9}
        };

        // 演算
        {
            using namespace std::execution;

            Matrix<Type> opsAdd  = opsCalc;
            Matrix<Type> opsSub  = opsCalc;
            Matrix<Type> opsMul  = opsCalc;
            Matrix<Type> opsHMul = opsCalc;
            Matrix<Type> opsHDiv = opsCalc;
            Matrix<Type> opsSMul = opsCalc;

            opsAdd += buf; // opsAdd.add<sequenced_policy>(buf);
            opsSub -= buf; // opsSub.sub<sequenced_policy>(buf);
            opsMul *= buf; // opsSub.mul<sequenced_policy>(buf);
            opsHMul ^= buf;// opsHMul.hadamardMul<sequenced_policy>(buf);
            opsHDiv /= buf;// opsHDiv.hadamardMul<sequenced_policy>(buf);
            opsSMul *= 2;  // opsSMul.scalarMul<sequenced_policy>(2);
        }
    }

    // matrixUtils.hpp
    {
        using Type = int;

        Matrix<Type> utilSize = Matrix<Type>::Size{ 3,4 };

        utilSize.resize(3,4);

        /* ------------------
            Rows:3
            Cols:4
        ------------------ */
        std::cout << "Rows:" << utilSize.rows() << std::endl << "Cols:" << utilSize.cols();
    }
}
