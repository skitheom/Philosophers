#include "philo.h"

int	convert_input_to_num(const char *str)
{
	char	*endptr;
	long	value;

	if (!str || !*str)
		return (-1);
	endptr = NULL;
	errno = 0;
	value = strtol(str, &endptr, 10);
	if (errno != 0 || *endptr != '\0' || value > INT_MAX || value < 0)
		return (-1);
	return ((int)value);
}

static bool	validate_argv(int argc, const char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		print_error(ERR_USAGE);
		return (false);
	}
	i = 1;
	while (i < argc)
	{
		if (convert_input_to_num(argv[i]) < 0 || (i != 5
				&& convert_input_to_num(argv[i]) == 0))
		{
			print_error(ERR_INVALID_INPUT);
			return (false);
		}
	}
	return (i == argc);
}

int	main(int argc, const char **argv)
{
	t_ctrl	ctrl;

	if (!validate_argv(argc, argv))
		return (EXIT_FAILURE);
	if (!init_ctrl(&ctrl, argc, argv))
	{
		print_error(ERR_INIT);
		return (EXIT_FAILURE);
	}
	if (!launch_threads(&ctrl, ctrl.philos, ctrl.config.num_of_philos))
	{
		print_error(ERR_LAUNCH_THREAD);
		cleanup_ctrl(&ctrl);
		return (EXIT_FAILURE);
	}
	cleanup_ctrl(&ctrl);
	return (EXIT_SUCCESS);
}
