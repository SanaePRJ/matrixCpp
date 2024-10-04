# matrixCpp
## �T�v
���̃v���W�F�N�g��**�V���v��**�Ȏ�������**�y��**�ȍs�񑀍���\�Ƃ��郉�C�u�����̊J����ړI�Ƃ��Ă��܂��B

> [!NOTE]
> �R���p�C����MSVC2022 C++17�Ƃ��܂��B

## �v�����@
�J���ɋ��͂��Ă���������͈ȉ��̕��@�ł��肢���܂��B

### �v��
1. ���|�W�g�����t�H�[�N���܂��B
2. �V�����u�����`���쐬���܂� (`git checkout -b feature/userName`).
3. �ύX���R�~�b�g���܂� (`git commit -m 'comment'`).
4. �u�����`�Ƀv�b�V�����܂� (`git push origin feature/userName`).
5. �v�����N�G�X�g���쐬���܂��B

## �N���X
### **matrix**�^
`template`��p����`int`��`double`�^�̍s��𐶐����܂��B  
```cpp
template<typename Type>
class Matrix{
	// member
}

Matrix<int> mint;
Matrix<double> mdouble;
```

�܂�[template�̓��ꉻ](https://en.wikipedia.org/wiki/Partial_template_specialization)���s��`float`��`double`�̂悤�Ȏ����^���w�肳�ꂽ�ꍇ�̂ݎg�p�ł��郁�\�b�h�����݂��܂��B  

## ����
 - �f�[�^�̊i�[
	�f�[�^��`std::vector<std::vector<Type>>`�Ŋi�[���������܂��B
	�����I��`CUDA`�Ȃ�GPU��ł̏������s�킹��\��ł��̂ňꎟ���z��֓W�J���郁�\�b�h���`���܂��B
 - �^�G�C���A�X
	`std::vector<std::vector<Type>>`�͎�������ۂɏ����������߈ȉ��̃R�[�h�ɂ��^�G�C���A�X`RowType`,`RowInitType`,`MatrixType`,`MatrixInitType`���`���܂��B
	�܂��N���X�O���ł��g�p�ł���悤`public`�ɂ��Ă����܂��B
	```cpp
	template<typename Type>
	class matrix{
	public:
		template<typename rowType    > using RowType     = std::vector<rowType>;
		template<typename rowInitType> using RowInitType = std::initializer_list<rowInitType>;

		template<typename matrixType = Type> using MatrixType     = std::vector          <RowType<matrixType>>;
		template<typename matrixType = Type> using MatrixInitType = std::initializer_list<RowInitType<matrixType>>;
	} 
	```
### �w�b�_�t�@�C��
���̃v���W�F�N�g�̃��C�u�����͕ێ琫����̂���`��`�t�@�C��`��`�����t�@�C��`�ɕ����鎖�Ƃ��܂��B
- ��`�t�@�C��
	- �N���X�̐錾
	- �֐��̃v���g�^�C�v�錾
	- �}�N���̒�`�Ȃ�
- �����t�@�C��
	- �֐��̎���
	- �����o�֐��̎���

#### Include Guard
�C���N���[�h�K�[�h�̖�����`MATRIXCPP_�t�@�C����_�g���q`�Ƃ��܂��B
```cpp
// test.hpp�̏ꍇ
#ifndef MATRIXCPP_TEST_HPP
#define MATRIXCPP_TEST_HPP

// proc...

#endif
```

#### ����
`.h`�͒�`�t�@�C���A`.hpp`�͎����t�@�C�����Ӗ����܂��B
 - matrix
	matrix.h matrixCalc.hpp�Ȃǂ��ׂẴt�@�C�����C���N���[�h���܂��B
 - matrix.h
	matrix�N���X�̒�`,�����o�֐��̃v���g�^�C�v�錾�Ȃǃ����o�̒�`���s���܂��B
 - matrixCalc.hpp
	���Z,���Z,�A�_�}�[���ςȂǌv�Z���s���܂��B
 - matrixOp.hpp
	���Z�q�֐��̎������s���܂��B
 - matrixDec.hpp
	LU�����ȂǍs�񕪉����s���܂��B�t�s����܂ށB
 - matrixUtils.hpp
	�s����ւ��ȂǍs��̑�����s���܂��B

```
matrix ---- matrix.h
        |-- matrixCalc.hpp
        |-- matrixOp.hpp
        |-- matrixDec.hpp
        |__ matrixUtils.hpp
```
#### 
## ����
- �����o����[`camelCase`](https://en.wikipedia.org/wiki/Camel_case)�ŋL�q���܂��B
- �N���X����`PascalCase`�ŋL�q���܂��B
- �v���C�x�[�g�����o
	�v���C�x�[�g�����o��(`camelCase`)�̌��`_`�����܂��B
- �v���g�^�C�v�錾
	`�Ԃ�l�^ �����o��(�����^1,�����^2,...);`

## �L�@
### ��`�t�@�C��
```cpp
template<typename Type>
class Matrix{
private:
	// �v���C�x�[�g�����o

	// �ϐ������o
	Type testValuePrivate_ = 0; // �R�����g

	// ���������o(�v���g�^�C�v�錾)
	Type testFuncPrivate_(const Matrix&,const Matrix&); // �R�����g

public:
	// �p�u���b�N�����o
	
	// �ϐ������o
	Type testValuePublic = 0; // �R�����g

	// ���������o(�v���g�^�C�v�錾)
	Type testFuncPublic(const Matrix&,const Matrix&); // �R�����g
}
```
### �����t�@�C��
```cpp

// �R�����g
template<typename Type>
Type Matrix<Type>::testFuncPrivate_(const Matrix& a,const Matrix& b){
	return Type();
}

// �R�����g
template<typename Type>
Type Matrix<Type>::testFuncPublic(const Matrix& a,const Matrix& b){
	return Type();
}
```

## �@�\�ꗗ
|����          |���Z�q |�֐�          |����                  |�Ԃ�l�^                                          |���ꉻ|
|----          |----   |----          |----                  |----                                              |----  |
|���          |=,<<   |None          |`MatrixInitType<Type>`  |`Matrix<Type>&`                                   |No    |
|�R�s�[        |=,<<   |None          |`const Matrix<Type>&` |`Matrix<Type>&`                                   |No    |
|���[�u���    |=      |None          |`Matrix<Type>&&`      |`Matrix<Type>&`                                   |No    |
|�s�Q��        |[]     |rowRef        |`size_t`              |`std::vector<Type>`/`std::reference_wrapper<Type>`|No    |
|��Q��        |None   |colRef        |`size_t`              |`std::vector<Type>`/`std::reference_wrapper<Type>`|No    |
|���Z          |+ , += |add           |`const Matrix<Type>&` |`Matrix<Type>`/`Matrix<Type>&`                    |No    |
|���Z          |- , -= |sub           |`const Matrix<Type>&` |`Matrix<Type>`/`Matrix<Type>&`                    |No    |
|��Z          |* , *= |mul           |`const Matrix<Type>&` |`Matrix<Type>`/`Matrix<Type>&`                    |No    |
|�X�J���{      |* , *= |scalarMul     |`const Matrix<Type>&` |`Matrix<Type>`/`Matrix<Type>&`                    |No    |
|�A�_�}�[����  |^ , ^= |hadamardMul   |`const Matrix<Type>&` |`Matrix<Type>`/`Matrix<Type>&`                    |No    |
|�A�_�}�[�����Z|/ , /= |hadamardDiv   |`const Matrix<Type>&` |`Matrix<Type>`/`Matrix<Type>&`                    |No    |
|LU����        |None   |luDec         |`void`                |`std::vector<Matrix<Type>>`                       |Yes   |
|�s��        |None   |det           |`void`                |`ty`                                              |No    |
|�t�s��        |None   |inverse       |`void`                |`Matrix<Type>`                                    |Yes   |
|�]�u          |None   |transpose     |`void`                |`Matrix<Type>`                                    |No    |
|�s����ւ�    |None   |swapRow       |`size_t`,`size_t`     |`Matrix<Type>&`                                   |No    |
|�����ւ�    |None   |swapCol       |`size_t`,`size_t`     |`Matrix<Type>&`                                   |No    |
|�T�C�Y�ύX    |None   |resize        |`size_t`,`size_t`     |`Matrix<Type>&`                                   |No    |
|�s�T�C�Y�擾  |None   |rows          |`void`                |`size_t`                                          |No    |
|��T�C�Y�擾  |None   |cols          |`void`                |`size_t`                                          |No    |
|�e�v�f�ւ̑���|None   |forEach       |`std::function<ty()>` |`Matrix<Type>&`                                   |No    |
|�e�v�f�ւ̑���|None   |forEach       |`std::function<ty(size_t,size_t,ty&)>`|`Matrix<Type>&`                   |No    |
> [!NOTE]
> ���̕���@�͒ǉ��\��[`QR����`,`�R���X�L�[����`,`�ŗL�l����`,`SVD����`,`�W�����_���W���``](https://en.wikipedia.org/wiki/Matrix_decomposition)