/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 03:05:06 by sakitaha          #+#    #+#             */
/*   Updated: 2024/10/24 16:38:33 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRTOL_H
# define FT_STRTOL_H

# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>

int		ft_isspace(int c);
void	skip_space(const char **str);
bool	check_sign(const char **str);
bool	is_valid_digit(char c, int base);
long	ft_strtol(const char *str, char **endptr, int base);
#endif
