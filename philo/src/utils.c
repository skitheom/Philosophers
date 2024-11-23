/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:15:01 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/23 18:52:25 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (size != 0)
	{
		i = 0;
		while (*src && i + 1 < size)
		{
			*(dest++) = *(src++);
			i++;
		}
		*dest = '\0';
	}
	return (srclen);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;

	destlen = 0;
	if (dest)
		destlen = ft_strlen(dest);
	if (size <= destlen)
		return (size + ft_strlen(src));
	while (*dest)
		dest++;
	srclen = ft_strlcpy(dest, src, size - destlen);
	return (destlen + srclen);
}

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
