#include "philo.h"

bool	validate_input(const char **argv)
{
	if (convert_input_to_num(argv[1]) <= 0 || convert_input_to_num(argv[2]) <= 0
		|| convert_input_to_num(argv[3]) <= 0
		|| convert_input_to_num(argv[4]) <= 0 || (argv[5]
			&& convert_input_to_num(argv[5]) <= 0))
		return (false);
	return (true);
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
	cleanup_ctrl(&ctrl);
	return (0);
}
