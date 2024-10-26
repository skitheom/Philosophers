#include "philo.h"

static bool	validate_argv(int argc, const char **argv)
{
	if (argc != 5 && argc != 6)
	{
		print_error(ERR_USAGE);
		return (false);
	}
	if (convert_input_to_num(argv[1]) <= 0 || convert_input_to_num(argv[2]) <= 0
		|| convert_input_to_num(argv[3]) <= 0
		|| convert_input_to_num(argv[4]) <= 0 || (argv[5]
			&& convert_input_to_num(argv[5]) <= 0))
	{
		print_error(ERR_INVALID_INPUT);
		return (false);
	}
	return (true);
}

int	main(int argc, const char **argv)
{
	t_ctrl	ctrl;

	if (!validate_argv(argc, argv))
	{
		cleanup_ctrl(&ctrl);
		return (1);
	}
	if (!init_ctrl(&ctrl, argc, argv))
	{
		cleanup_ctrl(&ctrl);
		print_error(ERR_MALLOC);
		return (1);
	}
	cleanup_ctrl(&ctrl);
	return (0);
}
