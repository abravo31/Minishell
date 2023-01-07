/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 00:06:26 by motero            #+#    #+#             */
/*   Updated: 2022/05/31 20:35:06 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	same_char(char *str)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = ft_strlen(str);
	while (str[i] != '\0' && i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (str[i] == str[j])
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_isprintable(char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
	{
		if (c[i] == 127 || c[i] < 32 || c[i] == 43 || c[i] == 45)
			return (1);
		i++;
	}
	return (0);
}

void	ft_putnbr_base(long int nbr, char *base)
{
	unsigned int	base_size;
	unsigned int	temp;

	base_size = ft_strlen(base);
	if (base_size <= 1 || ft_isprintable(base) == 1 || same_char(base) == 1)
		return ;
	if (nbr < 0)
	{
		ft_putchar('-');
		temp = -nbr;
	}
	else
		temp = nbr;
	if (temp < base_size)
		ft_putchar(base[temp]);
	if (temp >= base_size)
	{
		ft_putnbr_base(temp / base_size, base);
		ft_putnbr_base(temp % base_size, base);
	}
}

/*int		main(void)
{
	write(1, "42:", 3);
	ft_putnbr_base(42, "0123456789");
	write(1, "\n2a:", 4);
	ft_putnbr_base(42, "0123456789abcdef");
	write(1, "\n-2a:", 5);
	ft_putnbr_base(-42, "0123456789abcdef");
	write(1, "\n:", 2);
	ft_putnbr_base(42, "");
	write(1, "\n:", 2);
	ft_putnbr_base(42, "0");
	write(1, "\n:", 2);
	ft_putnbr_base(42, "+-0123456789abcdef");
	write(1, "\n:", 2);
	ft_putnbr_base(42, "\t0123456789abcdef");
	write(1, "-2147483648:", 11);
	ft_putnbr_base(-2147483648, "0123456789");
}*/
