/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:50:46 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/07 15:53:22 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	convert_input_to_num(const char *str)
{
	char	*endptr;
	long	value;

	if (!str || !*str)
		return (-1);
	endptr = NULL;
	errno = 0;
	value = ft_strtol(str, &endptr, 10);
	if (errno != 0 || *endptr != '\0' || value > INT_MAX || value < 0)
		return (-1);
	return ((int)value);
}

bool	validate_argv(int argc, const char **argv)
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
		if ((i != 5 && convert_input_to_num(argv[i]) == 0)
			|| convert_input_to_num(argv[i]) < 0)
		{
			print_error(ERR_INVALID_INPUT);
			return (false);
		}
		i++;
	}
	return (i == argc);
}
