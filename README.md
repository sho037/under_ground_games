# under_ground_games

## Description

### 実行環境

- c1-byod

　現在上記のみで動作確認済みですが、Dockerを利用し、他の環境でも動作するようにしたいと考えています。

### 実行方法

```bash
$ git clone ${this_repository}
$ cd under_ground_games
$ docker-compose up -d
$ docker-compose exec dev bash
$ make
$ ./uggames.exe
```