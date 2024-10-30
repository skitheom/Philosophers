#include "philo.h"

static void	setup_config(t_config *config, int argc, const char **argv)
{
	config->num_of_philos = convert_input_to_num(argv[1]);
	config->time_to_die = convert_input_to_num(argv[2]);
	config->time_to_eat = convert_input_to_num(argv[3]);
	config->time_to_sleep = convert_input_to_num(argv[4]);
	if (argc == 6 && argv[5])
		config->num_of_times_to_eat = convert_input_to_num(argv[5]);
	else
		config->num_of_times_to_eat = -1;
}

static bool	init_mutex_locks(t_ctrl *ctrl)
{
	if (pthread_mutex_init(&ctrl->dead_lock, NULL) != 0)
	{
		return (false);
	}
	if (pthread_mutex_init(&ctrl->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&ctrl->dead_lock);
		return (false);
	}
	if (pthread_mutex_init(&ctrl->write_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&ctrl->dead_lock);
		pthread_mutex_destroy(&ctrl->meal_lock);
		return (false);
	}
	if (pthread_mutex_init(&ctrl->error_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&ctrl->dead_lock);
		pthread_mutex_destroy(&ctrl->meal_lock);
		pthread_mutex_destroy(&ctrl->write_lock);
		return (false);
	}
	return (true);
}

static bool	init_mutex_forks(t_ctrl *ctrl)
{
	int	i;

	if (!ctrl->forks)
		return (false);
	i = 0;
	while (i < ctrl->config.num_of_philos)
	{
		if (pthread_mutex_init(&ctrl->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&ctrl->forks[i]);
			destroy_mutex_locks(ctrl);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	setup_philos(t_ctrl *ctrl)
{
	const size_t	current_time = get_current_time();
	const int		num_of_philos = ctrl->config.num_of_philos;
	int				i;

	if (current_time < 0)
		return (false);
	i = 0;
	while (i < num_of_philos)
	{
		ctrl->philos[i].id = i + 1;
		ctrl->philos[i].eaten_meals_count = 0;
		ctrl->philos[i].eating = false;
		ctrl->philos[i].last_meal = current_time;
		ctrl->philos[i].left_fork = &(ctrl->forks[i]);
		if (i == 0)
			ctrl->philos[i].right_fork = &(ctrl->forks[num_of_philos - 1]);
		else
			ctrl->philos[i].right_fork = &(ctrl->forks[i - 1]);
		ctrl->philos[i].ctrl = ctrl;
		i++;
	}
	return (true);
}

bool	init_ctrl(t_ctrl *ctrl, int argc, const char **argv)
{
	setup_config(&ctrl->config, argc, argv);
	ctrl->philos = malloc(sizeof(t_philo) * ctrl->config.num_of_philos);
	if (!ctrl->philos)
		return (false);
	ctrl->forks = malloc(sizeof(pthread_mutex_t) * ctrl->config.num_of_philos);
	if (!ctrl->forks || !init_mutex_locks(ctrl) || !init_mutex_forks(ctrl))
	{
		cleanup_memory(ctrl);
		return (false);
	}
	if (!setup_philos(ctrl))
	{
		cleanup_ctrl(ctrl);
		return (false);
	}
	ctrl->dead_flag = false;
	ctrl->error_flag = false;
	return (true);
}
