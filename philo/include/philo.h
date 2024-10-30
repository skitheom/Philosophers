#ifndef PHILO_H
# define PHILO_H

# include "ft_strtol.h"
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_config
{
	int					num_of_philos;
	size_t				time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_times_to_eat;
}						t_config;

typedef struct s_philo	t_philo;

typedef struct s_ctrl
{
	t_config			config;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		error_lock;
	bool				dead_flag;
	bool				error_flag;
}						t_ctrl;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					eaten_meals_count;
	bool				eating;
	size_t				last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_ctrl				*ctrl;

}						t_philo;

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define MAX_RETRY 100
# define USLEEP_RETRY_INTERVAL 100
# define PHILO_SLEEP_INTERVAL 1000

# define ERR_USAGE "Usage: ./philo num_of_philo die eat sleep (num_eating)\n"
# define ERR_INVALID_INPUT "Error: Invalid input value.\n"
# define ERR_INIT "Error: Initialization of control structure failed.\n"
# define ERR_LAUNCH_THREAD "Error: Failed to launch threads.\n"
# define ERR_JOIN_THREAD "Error: Failed to join threads.\n"
# define ERR_DEAD_FLAG "Error: Dead flag lock operation failed.\n"
# define ERR_ERROR_FLAG "Error: Error flag lock operation failed.\n"
# define ERR_WRITE "Error: Write operation failed.\n"
# define ERR_GET_TIME "Error: Failed to retrieve current time.\n"
# define ERR_PHILO_MSG "Error: Failed to print philosopher message.\n"

# define MSG_FORK_TAKEN "has taken a fork\n"
# define MSG_EAT "is eating\n"
# define MSG_SLEEP "is sleeping\n"
# define MSG_THINK "is thinking\n"
# define MSG_DIE "died\n"

void					*supervise(void *ptr);
bool					try_lock(t_ctrl *ctrl, pthread_mutex_t *lock);
void					eat(t_philo *philo);
void					*philo_routine(void *ptr);

/* cleanup.c */
void					destroy_mutex_locks(t_ctrl *ctrl);
void					destroy_mutex_forks(t_ctrl *ctrl);
void					xfree(void *ptr);
void					cleanup_memory(t_ctrl *ctrl);
void					cleanup_ctrl(t_ctrl *ctrl);

/* flags.c */
bool					set_error_flag_on(t_ctrl *ctrl);
bool					set_dead_flag_on(t_ctrl *ctrl);
bool					is_healthy(t_ctrl *ctrl);

/* ft_itoa.c */
char					*ft_itoa(int n);

/* init.c */
bool					init_ctrl(t_ctrl *ctrl, int argc, const char **argv);

/* main.c */
int						convert_input_to_num(const char *str);

/* print.c */
bool					print_error(const char *str);
bool					safe_print(t_ctrl *ctrl, int fd, const char *str);
bool					display_philo_msg(t_philo *philo, const char *str);

/* threads.c */
bool					launch_threads(t_ctrl *ctrl, t_philo *philos,
							int num_of_philos);

/* utils.c */
size_t					ft_strlen(const char *str);
size_t					ft_strlcpy(char *dest, const char *src, size_t size);
size_t					ft_strlcat(char *dest, const char *src, size_t size);
size_t					get_current_time(t_ctrl *ctrl);
void					philo_sleep(t_ctrl *ctrl, size_t time_to_sleep);
#endif

/*
The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking

When a philosopher has finished eating,
	they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.

•Every philosopher needs to eat and should never starve.
•Philosophers don’t speak with each other.
•Philosophers don’t know if another philosopher is about to die.
•No need to say that philosophers should avoid dying!

•Any state change of a philosopher must be formatted as follows:
◦timestamp_in_ms X has taken a fork
◦timestamp_in_ms X is eating
◦timestamp_in_ms X is sleeping
◦timestamp_in_ms X is thinking
◦timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
•A displayed state message should not be mixed up with another message.
•A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.
•Again, philosophers should avoid dying!
Your program must not have any data races.
 */
// Dream routine funtion
