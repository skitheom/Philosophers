# Philosophers

### Philosopherについて

**課題の概要**

- **課題名**: Philosophers
- **目的**: スレッド処理とミューテックスの基礎を学ぶ
- **シナリオ**: 哲学者が円卓に座り、食事、思考、睡眠を繰り返すシミュレーションを行う
- **目標**: 哲学者が死なずにバランスよく食事を続ける
- **課題内容**:
  - 複数の哲学者が存在し、それぞれが隣のフォークを使用して食事を行う
  - 哲学者は食事中は思考も睡眠もしない、思考中も睡眠中も同様
  - 哲学者が死ぬとシミュレーションは終了する
  - 哲学者間のフォークの取り合いを避けるために、ミューテックスでフォークの状態を保護する

- **実装要件**:
  - 各哲学者はスレッドとして実装
  - フォークは哲学者間で共有され、ミューテックスで管理
  - プログラムは指定された時間内に動作し、哲学者が適切に動作しなければならない
  - 全体のシミュレーションは死の回避を目的とする


### 使用許可関数

- **必須部分**:
  - `memset`
  - `printf`
  - `malloc`
  - `free`
  - `write`
  - `usleep`
  - `gettimeofday`
  - `pthread_create`
  - `pthread_detach`
  - `pthread_join`
  - `pthread_mutex_init`
  - `pthread_mutex_destroy`
  - `pthread_mutex_lock`
  - `pthread_mutex_unlock`

- **ボーナス部分**:
  - 上記に加えて以下の関数:
    - `fork`
    - `kill`
    - `exit`
    - `waitpid`
    - `sem_open`
    - `sem_close`
    - `sem_post`
    - `sem_wait`
    - `sem_unlink`

- **参考資料**:
  - **Operating Systems: Three Easy Pieces**（OSTEP）
  - **The C Programming Language** by Brian W. Kernighan and Dennis M. Ritchie
  - **Advanced Programming in the UNIX Environment** by W. Richard Stevens
  - [Thread-safety and POSIX.1](https://unix.org/whitepapers/reentrant.html)

https://www.evernote.com/shard/s97/client/snv?noteGuid=76e446df-1c78-45b6-b19b-696912d50f7e&noteKey=c932fea5a09fd302&sn=https%3A%2F%2Fwww.evernote.com%2Fshard%2Fs97%2Fsh%2F76e446df-1c78-45b6-b19b-696912d50f7e%2Fc932fea5a09fd302&title=Philosophers%25E3%2581%25A7%25E5%258F%2582%25E8%2580%2583%25E3%2581%25AB%25E3%2581%2597%25E3%2581%259F%25E3%2583%25AA%25E3%2583%25B3%25E3%2582%25AF

- [Philosophers 42 Guide— “The Dining Philosophers Problem”](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)
https://nafuka11.github.io/philosophers-visualizer/


### その他

- Linuxでの`fsainitize=thread -g`は`(uname -m) -R  ./philo {ARGV}`
- コンパイル時に、`$ setarch $(uname -m) -R ./philo {ARGV}`
