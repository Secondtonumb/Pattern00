課題3のソースコード
=
コンパイラする方法：
-
例：
`gcc -o pl pl.c`
`gcc -o pl_rec pl_rec.c`

実行方法：
-
pl: pattern learning, 学習データと初期重みを利用して、重みベクトルを計算する

`./pl learning_data.list init_weight.dat weight.dat [rho]`
`./pl weather.list wea_init_weight.dat weather_weight.dat [rho]`

pl_rec: pattern recognition, 重みベクトルを用いて、未知パターンを識別する

`./pl_rec weight.dat unknown.dat`
`./pl_rec weather_weight.dat unk_weather.dat`

テスト集（初期重み）の作り方：
-
まず以下のファイルを確かめる。
```
make_init_weight.py

1_create_init_weights.sh
2_create_weights.sh
3_rec.sh

random_init_weight.sh
```
次はテストデータを保存するディレクターを作る

`mkdir test_data`

テストデータを保存するディレクターを作る

`./random_init_weight.sh`

初期重み、修正重みがtest_dataに保存される

ソートされた識別結果が'recog_result'に保存される

なお、修正のプロセスがmake_weight.logに保存される