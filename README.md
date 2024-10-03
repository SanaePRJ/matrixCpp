# matrixCpp
## 概要
このプロジェクトは**シンプル**な実装かつ**軽量**な行列操作を可能とするライブラリの開発を目的としています。

## 貢献方法
開発に協力してくださる方は以下の方法でお願いします。

### 貢献
1. リポジトリをフォークします。
2. 新しいブランチを作成します (`git checkout -b feature/userName`).
3. 変更をコミットします (`git commit -m 'comment'`).
4. ブランチにプッシュします (`git push origin feature/userName`).
5. プルリクエストを作成します。

## クラス
### **matrix**型
`template`を用いて`int`や`double`型の行列を生成します。  
```cpp
template<typename ty>
class matrix{
	// member
}

matrix<int> mint;
matrix<double> mdouble;
```

また[templateの特殊化](https://en.wikipedia.org/wiki/Partial_template_specialization)を行い`float`や`double`のような実数型が指定された場合のみ使用できるメソッドが存在します。  

## 実装
 - データの格納
	データは`std::vector<std::vector<ty>>`で格納し処理します。
	将来的に`CUDA`などGPU上での処理を行わせる予定ですので一次元配列へ展開するメソッドを定義します。
 - 型エイリアス
	`std::vector<std::vector<ty>>`は実装する際に少し長いため以下のコードにより型エイリアス`row_t`,`rowInit_t`,`matrix_t`,`matrixInit_t`を定義します。
	またクラス外部でも使用できるよう`public`にしておきます。
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
## 命名
- 命名は[`camelCase`](https://en.wikipedia.org/wiki/Camel_case)を基本原則とします。

## 機能一覧
|操作          |演算子 |関数          |引数                  |返り値型                                      |特殊化|
|----          |----   |----          |----                  |----                                          |----  |
|代入          |=,<<   |None          |`matrixInit_t<ty>`    |`matrix<ty>&`                                 |No    |
|コピー        |=,<<   |None          |`const matrix<ty>&`   |`matrix<ty>&`                                 |No    |
|ムーブ代入    |=      |None          |`matrix<ty>&&`        |`matrix<ty>&`                                 |No    |
|行参照        |[]     |rowRef        |`size_t`              |`std::vector<ty>`/`std::reference_wrapper<ty>`|No    |
|列参照        |None   |colRef        |`size_t`              |`std::vector<ty>`/`std::reference_wrapper<ty>`|No    |
|加算          |+ , += |add           |`const matrix<ty>&`   |`matrix<ty>`/`matrix<ty>&`                    |No    |
|減算          |- , -= |sub           |`const matrix<ty>&`   |`matrix<ty>`/`matrix<ty>&`                    |No    |
|乗算          |* , *= |mul           |`const matrix<ty>&`   |`matrix<ty>`/`matrix<ty>&`                    |No    |
|スカラ倍      |* , *= |scalarMul     |`const matrix<ty>&`   |`matrix<ty>`/`matrix<ty>&`                    |No    |
|アダマール積  |^ , ^= |hadamardMul   |`const matrix<ty>&`   |`matrix<ty>`/`matrix<ty>&`                    |No    |
|アダマール除算|/ , /= |hadamardDiv   |`const matrix<ty>&`   |`matrix<ty>`/`matrix<ty>&`                    |No    |
|LU分解        |None   |luDec         |`void`                |`std::vector<matrix<ty>>`                     |Yes   |
|行列式        |None   |det           |`void`                |`ty`                                          |No    |
|逆行列        |None   |inverse       |`void`                |`matrix<ty>`                                  |Yes   |
|転置          |None   |transpose     |`void`                |`matrix<ty>`                                  |No    |
|行入れ替え    |None   |swapRow       |`size_t`,`size_t`     |`matrix<ty>&`                                 |No    |
|列入れ替え    |None   |swapCol       |`size_t`,`size_t`     |`matrix<ty>&`                                 |No    |
|サイズ変更    |None   |resize        |`size_t`,`size_t`     |`matrix<ty>&`                                 |No    |
|行サイズ取得  |None   |rows          |`void`                |`size_t`                                      |No    |
|列サイズ取得  |None   |cols          |`void`                |`size_t`                                      |No    |
|各要素への操作|None   |forEach       |`std::function<ty()>` |`matrix<ty>&`                                 |No    |
|各要素への操作|None   |forEach       |`std::function<ty(size_t,size_t,ty&)>`|`matrix<ty>&`                 |No    |
> [!NOTE]
> 他の分解法は追加予定[`QR分解`,`コレスキー分解`,`固有値分解`,`SVD分解`,`ジョルダン標準形`](https://en.wikipedia.org/wiki/Matrix_decomposition)