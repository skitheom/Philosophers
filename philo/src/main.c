#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

int64_t	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		print_error("Error: gettimeofday failed\n");
		return (-1);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	convert_input_to_num(const char *str)
{
	char	*endptr;
	long	value;

	if (!str || !*str)
		return (-1);
	endptr = NULL;
	errno = 0;
	value = strtol(str, &endptr, 10);
	// TODO: 条件の確認
	if (errno != 0 || *endptr != '\0' || value > INT_MAX || value < 0)
		return (-1);
	return ((int)value);
}

bool	validate_input(const char **argv)
{
	if (convert_input_to_num(argv[1]) <= 0 || convert_input_to_num(argv[2]) <= 0
		|| convert_input_to_num(argv[3]) <= 0
		|| convert_input_to_num(argv[4]) <= 0 || (argv[5]
			&& convert_input_to_num(argv[5]) <= 0))
		return (false);
	return (true);
}

t_shared_config	*init_shared_config(int argc, const char **argv)
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

bool	setup_philo_struct(t_ctrl *ctrl)
{
	int		i;
	int64_t	current_time;

	i = 0;
	current_time = get_current_time();
	if (current_time < 0)
		return (false);
	while (i < ctrl->config->num_of_philos)
	{
		ctrl->philos[i].config = ctrl->config;
		ctrl->philos[i].id = i + 1;
		ctrl->philos[i].meals_count = 0;
		ctrl->philos[i].eating = false;
		ctrl->philos[i].start_time = current_time;
		ctrl->philos[i].last_meal = current_time;
		ctrl->philos[i].left_fork = &(ctrl->forks[i]);
		if (i == 0)
			ctrl->philos[i].right_fork = &(ctrl->forks[ctrl->config->num_of_philos
					- 1]);
		else
			ctrl->philos[i].right_fork = &(ctrl->forks[i - 1]);
		ctrl->philos[i].dead_lock = &(ctrl->dead_lock);
		ctrl->philos[i].meal_lock = &(ctrl->meal_lock);
		ctrl->philos[i].write_lock = &(ctrl->write_lock);
		ctrl->philos[i].dead_flag = &(ctrl->dead_flag);
		i++;
	}
	return (true);
}

bool	init_philo_struct(t_ctrl *ctrl)
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

void	cleanup_ctrl(t_ctrl *ctrl)
{
	if (ctrl->config)
		free(ctrl->config);
	if (ctrl->philos)
		free(ctrl->philos);
	if (ctrl->forks)
		free(ctrl->forks);
}

int	main(int argc, const char **argv)
{
	t_ctrl	ctrl;

	if (argc != 5 && argc != 6)
	{
		print_error(ERR_USAGE);
		return (1);
	}
	if (!validate_input(argv))
	{
		print_error(ERR_INVALID_INPUT);
		return (1);
	}
	if (!init_ctrl(&ctrl, argc, argv))
	{
		print_error(ERR_MALLOC);
		return (1);
	}
	// 他の処理をここに追加
	cleanup_ctrl(&ctrl);
	printf("init success");
	return (0);
}
