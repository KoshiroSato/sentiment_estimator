# sentiment_estimator

辞書ベースの感情推定器。辞書は[SNOW D18:日本語感情表現辞書](https://www.jnlp.org/GengoHouse/snow/d18)を用いる。

## Usage
入力テキストを`input.txt`として、辞書とともに`data/`に用意し

```
docker-compose up -d --build
docker-compose exec sentiment bash
```
これにより前処理済みの辞書が`data/`に用意されるので、makeし

```
make
```
実行
```
./main
```
これで感情推定される。

例:
```
Positive Sentiment: 6
```