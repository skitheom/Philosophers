/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:13:58 by sakitaha          #+#    #+#             */
/*   Updated: 2024/10/31 16:50:29 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_msg
{
	t_philo				*philo;
	const char			*str;
}						t_msg;

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define MAX_RETRY 100
# define USLEEP_RETRY_INTERVAL 30
# define PHILO_SLEEP_INTERVAL 500
# define DELAY 5

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
bool					health_check(t_philo *philo);
bool					confirm_death(t_philo *philo, size_t time_to_die);
bool					get_eat_flag(t_philo *philo, bool *lock_success);

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

char					*ft_itoa(int n);
char					*ft_utoa(size_t num);

/* init.c */
bool					init_ctrl(t_ctrl *ctrl, int argc, const char **argv);

/* main.c */
int						convert_input_to_num(const char *str);

/* print.c */
bool					print_error(const char *str);
bool					safe_print(t_ctrl *ctrl, int fd, const char *str);
void					display_philo_msg(t_philo *philo, const char *str);

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
