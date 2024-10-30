#include "philo.h"

static size_t	count_digits(size_t num)
{
	size_t	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static void	num_to_str(size_t num, char *str, size_t len)
{
	while (len--)
	{
		str[len] = '0' + num % 10;
		num /= 10;
	}
}

char	*ft_utoa(size_t num)
{
	size_t	len;
	char	*str;

	len = count_digits(num);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	num_to_str(num, str, len);
	str[len] = '\0';
	return (str);
}
