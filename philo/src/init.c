#include "philo.h"

static t_shared_config	*init_shared_config(int argc, const char **argv)
{
	t_shared_config	*config;

	config = malloc(sizeof(t_shared_config));
	if (!config)
		return (NULL);
	memset(config, 0, sizeof(t_shared_config));
	config->num_of_philos = convert_input_to_num(argv[1]);
	config->time_to_die = convert_input_to_num(argv[2]);
	config->time_to_eat = convert_input_to_num(argv[3]);
	config->time_to_sleep = convert_input_to_num(argv[4]);
	if (argc == 6 && argv[5])
		config->num_of_times_to_eat = convert_input_to_num(argv[5]);
	else
		config->num_of_times_to_eat = -1;
	return (config);
}

static bool	init_philo_struct(t_ctrl *ctrl)
{
	ctrl->philos = malloc(sizeof(t_philo) * ctrl->config->num_of_philos);
	if (!ctrl->philos)
		return (false);
	memset(ctrl->philos, 0, sizeof(t_philo) * ctrl->config->num_of_philos);
	ctrl->forks = malloc(sizeof(pthread_mutex_t) * ctrl->config->num_of_philos);
	if (!ctrl->forks)
	{
		free(ctrl->philos);
		return (false);
	}
	memset(ctrl->forks, 0, sizeof(pthread_mutex_t)
		* ctrl->config->num_of_philos);
	return (true);
}

static void	setup_philo_helper(t_ctrl *ctrl, t_philo *philo)
{
	philo->config = ctrl->config;
	philo->meals_count = 0;
	philo->eating = false;
	philo->dead_lock = &(ctrl->dead_lock);
	philo->meal_lock = &(ctrl->meal_lock);
	philo->write_lock = &(ctrl->write_lock);
	philo->dead_flag = &(ctrl->dead_flag);
}

static bool	setup_philo_struct(t_ctrl *ctrl)
{
	int		num_of_philos;
	int		i;
	int64_t	current_time;

	current_time = get_current_time();
	if (current_time < 0)
		return (false);
	num_of_philos = ctrl->config->num_of_philos;
	i = 0;
	while (i < num_of_philos)
	{
		ctrl->philos[i].id = i + 1;
		ctrl->philos[i].start_time = current_time;
		ctrl->philos[i].last_meal = current_time;
		ctrl->philos[i].left_fork = &(ctrl->forks[i]);
		if (i == 0)
			ctrl->philos[i].right_fork = &(ctrl->forks[num_of_philos - 1]);
		else
			ctrl->philos[i].right_fork = &(ctrl->forks[i - 1]);
		setup_philo_helper(ctrl, &(ctrl->philos[i]));
		i++;
	}
	return (true);
}

bool	init_ctrl(t_ctrl *ctrl, int argc, const char **argv)
{
	ctrl->config = init_shared_config(argc, argv);
	if (!ctrl->config)
		return (false);
	if (!init_philo_struct(ctrl))
	{
		print_error(ERR_MALLOC);
		free(ctrl->config);
		return (false);
	}
	if (!setup_philo_struct(ctrl))
	{
		free(ctrl->config);
		free(ctrl->philos);
		free(ctrl->forks);
		return (false);
	}
	return (true);
}
