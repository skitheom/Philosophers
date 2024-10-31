# Mandatory Part

## Program Information

- **Program Name**: `philo`
- **Turn in Files**:
  - `Makefile`
  - `*.h`
  - `*.c`
  - (All files must be placed in the `philo/` directory)
- **Makefile Rules**:
  - `NAME`, `all`, `clean`, `fclean`, `re`

## Arguments
- `number_of_philosophers`: The number of philosophers and forks.
- `time_to_die`: Time (in milliseconds) before a philosopher dies without eating.
- `time_to_eat`: Time (in milliseconds) it takes for a philosopher to eat.
- `time_to_sleep`: Time (in milliseconds) a philosopher spends sleeping.
- `[number_of_times_each_philosopher_must_eat]` (Optional): The simulation stops if each philosopher has eaten this number of times. If not specified, the simulation ends when a philosopher dies.

## External Functions Allowed
- `memset`
- `printf`
- `malloc`
- `free`
- `write`
- `usleep`
- `gettimeofday`
- `pthread_create`
- `pthread_detach`: スレッドが終了した際に自動的にリソースを解放するための関数
- `pthread_join`: スレッドの終了を待機する関数。メインスレッドが他のスレッドの終了を待つ際に使う
- `pthread_mutex_init`: ミューテックス（排他制御オブジェクト）を初期化する関数。フォークの使用を管理するために使う
- `pthread_mutex_destroy`: 使用済みのミューテックスを破棄する関数。プログラム終了時に使う
- `pthread_mutex_lock`: ミューテックスをロックして、他のスレッドがリソースにアクセスするのを防ぐ関数
- `pthread_mutex_unlock`: ロックされたミューテックスを解除して、他のスレッドがリソースにアクセスできるようにする関数

## Libft Authorized
- **No**

## Description
- The project simulates the **Dining Philosophers Problem** using **threads** and **mutexes**.

## Specific Rules
1. Each philosopher should be represented as a thread.
2. There is **one fork between each pair of philosophers**:
   - If there are several philosophers, each philosopher has a fork on their left and right side.
   - If there is only **one philosopher**, there should only be **one fork** on the table.
3. The forks must be protected using **mutexes** to prevent two philosophers from taking the same fork at the same time.

## 参考資料

