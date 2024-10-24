# Bonus Part

## Program Information

- **Program Name**: `philo_bonus`
- **Turn in Files**:
  - `Makefile`
  - `*.h`
  - `*.c`
  - (All files must be placed in the `philo_bonus/` directory)
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
- `fork`
- `kill`
- `exit`
- `pthread_create`
- `pthread_detach`
- `pthread_join`
- `usleep`
- `gettimeofday`
- `waitpid`
- `sem_open`: 名前付きセマフォを作成または開く関数。プロセス間でリソースを共有するためのセマフォを使うときに利用する
- `sem_close`: セマフォを閉じる関数。sem_openで開いたセマフォを使い終わった後に呼び出して、リソースを解放する
- `sem_post`: セマフォの値をインクリメント（+1）して、セマフォを解放する関数。リソースを利用可能にするときに使う
- `sem_wait`: セマフォの値をデクリメント（-1）し、セマフォが0になるまで待機する関数。リソースを占有する前に呼び出
- `sem_unlink`: 名前付きセマフォを削除する関数。セマフォを完全に削除して、将来のプロセスからアクセスできなくする

## Libft Authorized
- **No**

## Description
- The project simulates the **Dining Philosophers Problem** using **processes** and **semaphores**.

## Specific Rules
1. All the forks are placed in the middle of the table and managed using **semaphores**.
2. Forks are not represented as individual states in memory, but as the number of available forks tracked by a semaphore.
3. Each philosopher should be a **process**. However, the main process should not act as a philosopher.

## Important Note
- The bonus part will **only be evaluated** if the **mandatory part is completed perfectly**. This means that the mandatory part must meet **all requirements** and function without any malfunctions. If the mandatory part is not perfect, the bonus part will not be considered for evaluation.
