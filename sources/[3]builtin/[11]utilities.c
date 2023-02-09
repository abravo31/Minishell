/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [11]utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:48:47 by motero            #+#    #+#             */
/*   Updated: 2023/02/09 22:56:09 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_isspace(int c)
{
	return (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v'
		|| c == ' ');
}

static long long	ft_max_min(int sign)
{
	if (sign == 1)
		return (__LONG_LONG_MAX__);
	else
		return (LLONG_MIN);
}

long long	ft_atoll(const char *nptr)
{
	long long		num;
	int				sign;
	long long		bdr;
	char			c;

	num = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		(void)*nptr++;
	c = *nptr;
	if (c == '-' || c == '+')
		sign = 1 - (2 * (*nptr++ == '-'));
	while (ft_isdigit(*nptr))
	{
		bdr = __LONG_LONG_MAX__ / 10;
		if ((num > bdr || num == bdr) && ((*nptr - '0') > 7))
			return (ft_max_min(sign));
		num = 10 * num + (*nptr++ - '0');
	}
	return (num * sign);
}

/* Check for number bigger than long long max */
int	is_big_number(long long num, char *str)
{
	int			i;
	char		c;
	int			last_digit;

	if (num < 0)
		num = -num;
	i = ft_strlen(str) - 1;
	c = str[i];
	last_digit = num % 10;
	num = num / 10;
	while (c == (48 + last_digit) && i)
	{
		c = str[--i];
		last_digit = num % 10;
		num = num / 10;
	}
	while (c == '0' && i)
		c = str[--i];
	if ((c == '-' || c == '+') && i == 0)
		return (1);
	if (i)
		return (0);
	return (1);
}
