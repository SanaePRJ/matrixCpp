#include <iostream>
#include "matrixLib/matrix"


int main()
{
    // matrixCtor.hpp - demoCode
    {
        using Type = int;

        Matrix<Type> ctor1; // 指定なし

        Matrix<Type> ctor2 =
        {
            {1,2,3},
            {4,5,6},
            {7,8,9}
        }; // 値指定

        Matrix<Type> ctor3 = Matrix<Type>::Size{3,3}; // サイズ指定

        Matrix<Type> ctor4 = ctor2;            // コピー
        Matrix<Type> ctor5 = std::move(ctor2); // move
    }

    // matrixOps.hpp - demoCode
    {
        using Type = int;

        Matrix<Type> ops1;
        ops1 = { {1,2,3} };

        Matrix<Type> ops2;
        ops2 = ops1;

        Matrix<Type> ops3;
        ops3 << Matrix<Type>::MatrixInitType<Type>{{1,2,3}};

        Matrix<Type> ops4;
        ops4 << ops3;

        Matrix<Type> ops5;
        ops5 << std::move(ops4);

        for (auto& row_ : ops5[0])
            std::cout << row_;
    }
}
