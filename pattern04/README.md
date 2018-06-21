課題3のソースコード
=
コンパイラする方法：
-
例：
`gcc -o nw nw.c`

`gcc -o rec rec.c`

プログラム解説：
-
#nw: network_training ニューネルネットワークのパラメータのトレーニングを行う。

`"Usage: ./nw\t <training_pattern_list>\n"
	 "\t<init_bias>\t" "<init_weight_list_for_training>\n"
         "\t<bias_training_output>\t" "<weights_training_output_list>\n"
         "\t<TRAINING LOG>"`
	 
ただし、収束条件を三つを提供している。

0. 学習パターンに応じるクラスターの出力は全部の出力の最大値である場合、収束として認める（弱収束条件）
1. 学習パターンに応じるクラスターの出力は上限閾値を超え、かつ以外の出力は下限閾値以下(強収束条件)
2. epoch は人為で決める（テスト用）

nw を実行する際にガイダンスは出てくるためそれを参照してください。

#rec: recognition 未知パターンの認識を行う。
`"Usage: ./rec <testset.list>\n"
           "\t<trained_bias> <trained_weights.list>"`
	   
実行方法：
-
まずディレクトリ`exp`の存在を確かめる。
```
$ tree exp
exp
├── test
│   ├── bias.dat
│   ├── p.list
│   ├── ptns
│   │   └── 1.dat
│   ├── w.list
│   └── weights
│       ├── weight_0.dat
│       └── weight_1.dat
└── train
    ├── bias.dat
    ├── p.list
    ├── ptns
    │   ├── x1_0.dat
    │   ├── x2_0.dat
    │   ├── x3_1.dat
    │   ├── x4_1.dat
    │   ├── x5_2.dat
    │   └── x6_2.dat
    ├── w.list
    └── weights
        ├── weight_0.dat
        └── weight_1.dat

6 directories, 17 files
```
ファイルが一致していなくともいいですが、ディレクトリ及びファイルの構造を一致にしてください。

#学習及び認識を行う場合
##認識:

`./rec.sh`

#学習のプロセスを可視化する場合：
必要とする環境：

```
python

numpy
matplotlib.pyplot
argparse
pandas
```
そして、

`./plot.sh`

によって、各パターンの訓練プロセスが見える。

なお、訓練プロセスがlog.csvに保存されている。

plotもこのファイルに依存し可視化になる。

