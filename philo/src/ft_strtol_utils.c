/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 03:44:13 by sakitaha          #+#    #+#             */
/*   Updated: 2024/10/24 16:38:22 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strtol.h"

int	ft_isspace(int c)
{
	return (('\t' <= c && c <= '\r') || c == ' ');
}

void	skip_space(const char **str)
{
	while (ft_isspace(**str))
	{
		(*str)++;
	}
}

bool	check_sign(const char **str)
{
	bool	is_negative;

	is_negative = (**str == '-');
	if (**str == '-' || **str == '+')
	{
		(*str)++;
	}
	return (is_negative);
}

bool	is_valid_digit(char c, int base)
{
	if (base == 0)
	{
		return ('0' <= c && c <= '9');
	}
	if (base <= 10)
	{
		return ('0' <= c && c < '0' + base);
	}
	return (('0' <= c && c <= '9') || ('A' <= c && c < 'A' + base - 10)
		|| ('a' <= c && c < 'a' + base - 10));
}
