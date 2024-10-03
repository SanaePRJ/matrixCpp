# matrixCpp
## �T�v
���̃v���W�F�N�g��**�V���v��**�Ȏ�������**�y��**�ȍs�񑀍���\�Ƃ��郉�C�u�����̊J����ړI�Ƃ��Ă��܂��B

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
template<typename ty>
class matrix{
	// member
}

matrix<int> mint;
matrix<double> mdouble;
```

�܂�[template�̓��ꉻ](https://en.wikipedia.org/wiki/Partial_template_specialization)���s��`float`��`double`�̂悤�Ȏ����^���w�肳�ꂽ�ꍇ�̂ݎg�p�ł��郁�\�b�h�����݂��܂��B  

## ����
 - �f�[�^�̊i�[
	�f�[�^��`std::vector<std::vector<ty>>`�Ŋi�[���������܂��B
	�����I��`CUDA`�Ȃ�GPU��ł̏������s�킹��\��ł��̂ňꎟ���z��֓W�J���郁�\�b�h���`���܂��B
 - �^�G�C���A�X
	`std::vector<std::vector<ty>>`�͎�������ۂɏ����������߈ȉ��̃R�[�h�ɂ��^�G�C���A�X`row_t`,`rowInit_t`,`matrix_t`,`matrixInit_t`���`���܂��B
	�܂��N���X�O���ł��g�p�ł���悤`public`�ɂ��Ă����܂��B
	```cpp
	template<typename ty>
	class matrix{
	public:
		template<typename rowType    > using row_t     = std::vector<rowType>;
		template<typename rowInitType> using rowInit_t = std::initializer_list<rowInitType>;

		template<typename matrixType = ty> using matrix_t     = std::vector          <row_t<matrixType>>;
		template<typename matrixType = ty> using matrixInit_t = std::initializer_list<rowInit_t<matrixType>>;
	} 
	```
## ����
- ������[`camelCase`](https://en.wikipedia.org/wiki/Camel_case)����{�����Ƃ��܂��B

## �@�\�ꗗ
|����          |���Z�q |�֐�          |����                  |�Ԃ�l�^                                      |���ꉻ|
|----          |----   |----          |----                  |----                                          |----  |
|���          |=,<<   |None          |`matrixInit_t<ty>`    |`matrix<ty>&`                                 |No    |
|�R�s�[        |=,<<   |None          |`const matrix<ty>&`   |`matrix<ty>&`                                 |No    |
|���[�u���    |=      |None          |`matrix<ty>&&`        |`matrix<ty>&`                                 |No    |
|�s�Q��        |[]     |rowRef        |`size_t`              |`std::vector<ty>`/`std::reference_wrapper<ty>`|No    |
|��Q��        |None   |colRef        |`size_t`              |`std::vector<ty>`/`std::reference_wrapper<ty>`|No    |
|���Z          |+ , += |add           |`const matrix<ty>&`   |`matrix<ty>`/`matrix<ty>&`                    |No    |
|���Z          |- , -= |sub           |`const matrix<ty>&`   |`matrix<ty>`/`matrix<ty>&`                    |No    |
|��Z          |* , *= |mul           |`const matrix<ty>&`   |`matrix<ty>`/`matrix<ty>&`                    |No    |
|�X�J���{      |* , *= |scalarMul     |`const matrix<ty>&`   |`matrix<ty>`/`matrix<ty>&`                    |No    |
|�A�_�}�[����  |^ , ^= |hadamardMul   |`const matrix<ty>&`   |`matrix<ty>`/`matrix<ty>&`                    |No    |
|�A�_�}�[�����Z|/ , /= |hadamardDiv   |`const matrix<ty>&`   |`matrix<ty>`/`matrix<ty>&`                    |No    |
|LU����        |None   |luDec         |`void`                |`std::vector<matrix<ty>>`                     |Yes   |
|�s��        |None   |det           |`void`                |`ty`                                          |No    |
|�t�s��        |None   |inverse       |`void`                |`matrix<ty>`                                  |Yes   |
|�]�u          |None   |transpose     |`void`                |`matrix<ty>`                                  |No    |
|�s����ւ�    |None   |swapRow       |`size_t`,`size_t`     |`matrix<ty>&`                                 |No    |
|�����ւ�    |None   |swapCol       |`size_t`,`size_t`     |`matrix<ty>&`                                 |No    |
|�T�C�Y�ύX    |None   |resize        |`size_t`,`size_t`     |`matrix<ty>&`                                 |No    |
|�s�T�C�Y�擾  |None   |rows          |`void`                |`size_t`                                      |No    |
|��T�C�Y�擾  |None   |cols          |`void`                |`size_t`                                      |No    |
|�e�v�f�ւ̑���|None   |forEach       |`std::function<ty()>` |`matrix<ty>&`                                 |No    |
|�e�v�f�ւ̑���|None   |forEach       |`std::function<ty(size_t,size_t,ty&)>`|`matrix<ty>&`                 |No    |
> [!NOTE]
> ���̕���@�͒ǉ��\��[`QR����`,`�R���X�L�[����`,`�ŗL�l����`,`SVD����`,`�W�����_���W���``](https://en.wikipedia.org/wiki/Matrix_decomposition)