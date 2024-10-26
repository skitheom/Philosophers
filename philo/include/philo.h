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

// 読み取り専用の構造体
typedef struct s_shared_config
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_to_eat;
}					t_shared_config;

typedef struct s_philo
{
	t_shared_config	*config;
	int				id;
	int				meals_count;
	bool			eating;
	int64_t			start_time;
	int64_t			last_meal;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	bool			*dead_flag;
	pthread_t		thread;

}					t_philo;

typedef struct s_ctrl
{
	t_shared_config	*config;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	bool			dead_flag;
}					t_ctrl;

# define ERR_USAGE "Usage: ./philo num_of_philo die eat sleep (num_eating)\n"
# define ERR_INVALID_INPUT "Error: Invalid input value\n"
# define ERR_MALLOC "Error: Memory allocation failed\n"

bool				init_ctrl(t_ctrl *ctrl, int argc, const char **argv);
void				print_error(char *str);
void				cleanup_ctrl(t_ctrl *ctrl);
int					convert_input_to_num(const char *str);
int64_t				get_current_time(void);

#endif
