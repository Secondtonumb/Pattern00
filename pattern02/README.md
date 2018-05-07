課題2のソースコード

`learning_data`,`prototype_data`,`unrecog_data` の中に学習データ、プロトタイプデータ、評価データがそれぞれ保存されている。

`data_process.h` には行列データの処理に関する関数が保存されている。

`file.h` にはファイルから有効情報を得る、あるいは、プログラムからファイルへの出力に関する関数が保存されている。

`sort.h` には評価用の関数、つまり、結果を人間ではなく、プログラムに判断させてもらう関数が保存されている。

コンパイラ方法：

例：`gcc -o knn knn.c`

実行方法：

knn:k近傍法で未知パターンを評価する, "k"は引数として使える

`./knn learning.list unrecognized_data/pattern2-5.dat <k>`

make_proto:学習パターンから、プロトタイプを生成する。

`./make_proto learning.list proto.list`

proto_nnm:プロトタイプを用いて、未知パターンを最近傍法で評価する。

`./proto_nnm proto.list unrecognized_data/pattern2-5.dat`
