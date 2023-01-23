/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:43:10 by motero            #+#    #+#             */
/*   Updated: 2022/05/31 14:59:45 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	index_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	check_error(char *c)
{
	unsigned int	sz;
	int				is_printable;
	unsigned int	i;
	unsigned int	j;
	int				same_char;

	sz = ft_strlen(c);
	is_printable = 0;
	same_char = 0;
	i = 0;
	while (c[i] != '\0' && i < sz)
	{
		if (c[i] == 127 || c[i] <= 32 || c[i] == 43 || c[i] == 45)
			is_printable = 1;
		j = i + 1;
		while (j < sz)
		{
			if (c[i] == c[j])
				same_char = 1;
			j++;
		}
		i++;
	}
	return (sz <= 1 || is_printable == 1 || same_char == 1);
}

int	ft_isspace_lsign(char *c)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (c[i] == 32 || (c[i] >= 9 && c[i] <= 13))
		i++;
	while (c[i] == 43 || c[i] == 45)
	{
		if (c[i] == 45)
			sign = -sign;
		i++;
	}
	return (sign * i);
}

int	ft_atoi_base(char *str, char *base)
{
	int				length;
	int				sign;
	unsigned int	num;
	int				base_size;

	sign = 1;
	if (check_error(base) == 1)
		return (0);
	length = ft_isspace_lsign(str);
	if (length < 0)
	{
		length = -length;
		sign = -1;
	}
	num = 0;
	base_size = ft_strlen(base);
	while (str[length])
	{
		if (index_in_base(str[length], base) == -1)
			return (0);
		num *= base_size;
		num += index_in_base(str[length], base);
		length++;
	}	
	return (sign * num);
}

/*int	main(void)
{
	printf("42:%d\n", ft_atoi_base("  \n  42t4457","0123456789"));
	printf("-42:%d\n", ft_atoi_base(" --+-42sfs:f545","0123456789"));
	printf("0:%d\n", ft_atoi_base("\0 1337","0123456789"));
	printf("0:%d\n", ft_atoi_base("-0","0123456789"));
	printf("0:%d\n", ft_atoi_base(" - 1 3 2 5 6 3 2 1 6 7","0123456789"));
	printf("-1325632167:%d\n", ft_atoi_base("-1325632167","0123456789"));
	printf("-100:%d\n", ft_atoi_base("-100","0123456789"));
	printf("min:%d\n", ft_atoi_base("\t---+2147483648","0123456789"));
	printf("max:%d\n", ft_atoi_base("\v2147483647","0123456789"));
}*/

/*int	main(void)
{
	printf("61:%d\n", ft_atoi_base("     +-+-+--10001", "01"));
	printf("-42:%d\n", ft_atoi_base("   --------+-2a", "0123456789abcdef"));
	printf("42:%d\n", ft_atoi_base("   -+-2a", "0123456789abcdef"));
	printf("0:%d\n", ft_atoi_base("   --------+- 2a", "0123456789abcdef"));
	printf("0:%d\n", ft_atoi_base("   --------+-z", "0123456789abcdef"));
	printf("0:%d\n", ft_atoi_base("   --------+-2a", ""));
	printf("0:%d\n", ft_atoi_base("   --------+-2a", "0"));
	printf("0:%d\n", ft_atoi_base("   --------+-2a", "+-0"));
	printf("0:%d\n", ft_atoi_base("   --------+-2a", "\t01"));
}*/
