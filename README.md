## 使い方

```
$ ./setup.sh
$ ruby sample.rb
```

## 再現環境
* Ruby 2.6.0 以降
* macOS 10.15 (試した環境)

## 問題の説明
macOS 上で Ruby 2.6.0 以降を使用した際に、拡張ライブラリ内で `fork()/exec()` で外部コマンドを実行したあと `waitpid()` をコールすると失敗するようになりました。
私がメンテナンスしている RMagick 利用している ImageMagick が PDF を処理する際にこのような処理を行っており、macOS + Ruby 2.6.0 以降で処理に失敗するようになり困っております。

https://github.com/Watson1978/rmagick-issue483 に再現コードを用意しており、以下の様に実行していただくと Ruby 2.6.0 以降でエラー終了します。

```
$ ./setup.sh
$ ruby sample.rb
$ ruby sample.rb
Ruby v2.6.0
Error waitpid(): Interrupted system call
```

```
$ ./setup.sh
$ ruby ./sample.rb
Ruby v2.6.5
Error waitpid(): Interrupted system call
```



Ruby 2.5.x 以下ですと期待通りに `WIFEXITED` のパスを通り正常に終了します。

```
$ ./setup.sh
$ ruby sample.rb
Ruby v2.5.7
(1) WIFEXITED : status = 0
```

```
$ ./setup.sh
$ ruby sample.rb
Ruby v2.3.8
(1) WIFEXITED : status = 0
```

確認した限り、macOS 上だけでこの現象が発生します。
