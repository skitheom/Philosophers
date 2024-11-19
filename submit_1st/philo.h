/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:13:58 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/18 02:21:43 by sakitaha         ###   ########.fr       */
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

typedef struct s_msg
{
	u_int64_t			timestamp;
	int					id;
	const char			*str;
	struct s_msg		*next_msg;
}						t_msg;

typedef struct s_philo	t_philo;

typedef struct s_ctrl
{
	int					num_of_philos;
	u_int64_t			time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_of_times_to_eat;
	u_int64_t			start_time;

	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		locks[4];

	bool				dead_flag;
	bool				error_flag;
	t_msg				*msg_queue;
}						t_ctrl;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					eaten_meals_count;
	bool				eating;
	u_int64_t			last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_ctrl				*ctrl;
}						t_philo;

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define MAX_RETRY 300
# define USLEEP_RETRY_INTERVAL 100
# define SUPERVISE_SLEEP_INTERVAL 500
# define PRINT_SLEEP_INTERVAL 100
# define PHILO_SLEEP_INTERVAL 100
# define DELAY 5

# define NUM_LOCKS 4
# define DEAD_LOCK 0
# define MEAL_LOCK 1
# define MSG_LOCK 2
# define ERROR_LOCK 3

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
void					eat(t_philo *philo);
void					*philo_routine(void *ptr);

/* clean up */
void					destroy_mutexes(pthread_mutex_t mutexes[], int size);
void					xfree(void *ptr);
void					cleanup_memory(t_ctrl *ctrl);
void					cleanup_ctrl(t_ctrl *ctrl);
void					cleanup_msg(t_ctrl *ctrl);

/* flag */
bool					get_eat_flag(t_philo *philo, bool *lock_success);
bool					set_eat_flag(t_philo *philo, bool state);
bool					set_eat_flag_on(t_philo *philo,
							u_int64_t beginning_of_last_meal);
bool					set_eat_flag_off(t_philo *philo);
bool					get_dead_flag(t_ctrl *ctrl);
bool					set_dead_flag_on(t_ctrl *ctrl);
bool					get_error_flag(t_ctrl *ctrl);
bool					set_error_flag_on(t_ctrl *ctrl);

/* health */
bool					all_healthy(t_ctrl *ctrl);
bool					is_healthy(t_ctrl *ctrl);
bool					self_health_check(t_philo *philo);

/* init */
bool					init_ctrl(t_ctrl *ctrl, const char **argv);

/* philo_routine */

/* print */
bool					print_error(const char *str);
void					print_message(t_msg *msg);
void					*print_routine(void *ptr);
void					display_message(t_ctrl *ctrl, u_int64_t cur_ts, int id,
							const char *str);

/* threads.c */
bool					try_lock(pthread_mutex_t *lock);
bool					launch_threads(t_ctrl *ctrl, t_philo *philos);

/* time.c */
u_int64_t				get_current_time(void);
u_int64_t				get_elapsed_time(t_ctrl *ctrl);

/* utils.c */
int						ft_strncmp(const char *s1, const char *s2, size_t n);
size_t					ft_strlen(const char *str);
size_t					ft_strlcpy(char *dest, const char *src, size_t size);
size_t					ft_strlcat(char *dest, const char *src, size_t size);
void					philo_sleep(t_ctrl *ctrl, u_int64_t time_to_sleep);

/* validate_arg.c */
int						convert_input_to_num(const char *str);
bool					validate_argv(int argc, const char **argv);

#endif
