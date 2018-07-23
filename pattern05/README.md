課題5のソースコード
=
コンパイラする方法：
-
課題５.１：
`gcc -o cart cart.c # 識別木の生成` 

`gcc -o rec rec.c # 識別木で未知パターンの認識`

課題５.2：
`gcc -o cart cart.c`

`gcc -o rec rec.c`

`gcc -o sampling sampling.c # 重み付きサンプリング`

`gcc -o adaboost adaboost.c # Adaboost で識別器重み更新`

`gcc -o strong strong.c # 強識別器で未知パターンの認識`


プログラム解説：
-
cart: 未知パターンの各次元において弱識別器の構築。

```
Usage: ./cart ptns.dat forest.dat
```


rec: recognition 弱識別器の中で一番分離性能の良いの用いて、未知パターンの認識を行う。

```
Usage: ./rec rec.dat forest.dat
```


sampling: 学習パターンの重みでサンプリングする。

```
Usage: ./resamp ptns.dat resamp.dat <resamples_num>
```

Adaboost: Adaboost手法で重み付きサンプルを利用し、弱識別器の重みを修正する。

```
Usage: resamp.dat forest.dat new_forest.dat
```

Strong: 強識別器で未知パターンを識別する。

```
Usage: ./strong rec.dat new_forest.dat
```

実行方法：
==
課題5.1
--
まずディレクトリ`kadai5_1`に入り、下記のファイルをチェックする。
```
.
├── cart.c
├── data.h
├── dt.sh
├── evalution.h
├── file.h
├── forest.dat
├── ptns.dat
├── rec.c
├── rec.dat
└── sort.h
```
実行手順:
```
./dt.sh
```
課題5.2
-
まずディレクトリ`kadai5_2`に入り、下記の`*`が付いているファイルをチェックする。

```
.
├── ada.log
├── ada.sh		*　重みsampling、adaboost および識別器用スクリプト
├── adaboost.c		*　ソースコード
├── cart.c		*　ソースコード
├── data.h
├── dt.sh		*　決定木生成、識別用スクリプト
├── evalution.h		*　ソースコード
├── file.h		*　ソースコード
├── forest.dat		*　各次元決定木の保存先
├── grid.dat		
├── grid.py			
├── label.csv		
├── label.dat		
├── new_f.dat		
├── new_forest.dat	*　重みづき決定木の保存先
├── plot.c
├── plot.py
├── plot.sh
├── ptns.dat
├── rec.c		*　ソースコード
├── rec.dat
├── resamp.dat		*　重み付きサンプルの保存先
├── sampling.c		*　ソースコード
├── sort.h		*
└── strong.c		*　ソースコード
```


実行手順:

```
./dt.sh
./adaboost.sh

```
可分離領域を可視化する場合：

まず以下の環境が完備していることをチェック。
```
python

numpy
matplotlib.pyplot
argparse
pandas
```

そして、

`./plot.sh new_forest.dat(重みづき決定木の保存先)`

によって、Adaboostでできた強識別器の識別領域が見える。
![image](https://github.com/Secondtonumb/pattern_recogn/blob/master/pattern05/kadai5_2/Ada.png)

なお、識別器重み修正プロセスがada.logに保存されている。


