/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_switch_cases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:13:05 by motero            #+#    #+#             */
/*   Updated: 2022/11/23 01:27:22 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_single_char(int c)
{
	int	len;

	len = 0;
	ft_putchar(c);
	len++;
	return (len);
}

int	ft_string(char *s)
{
	int	len;

	if (!s)
	{
		ft_putstr("(null)");
		return (6);
	}
	else
	{
		ft_putstr(s);
		len = ft_strlen(s);
		return (len);
	}
}

int	ft_address(unsigned long ptr)
{
	if (ptr)
		return (ft_print_addr(ptr) + 2);
	else
	{
		ft_putstr("(nil)");
		return (5);
	}
}

int	ft_nbr_signed(int nbr)
{
	int	len_nbr;

	ft_putnbr_base(nbr, "0123456789");
	len_nbr = 0;
	if (nbr <= 0)
		len_nbr += 1;
	while (nbr)
	{
		nbr /= 10;
		len_nbr += 1;
	}
	return (len_nbr);
}

int	ft_nbr_unsigned(char c, long int nbr)
{
	int	len_nbr;
	int	base;

	base = 16;
	if (c == 'u')
	{
		ft_putnbr_base(nbr, "0123456789");
		base = 10;
	}
	else if (c == 'x')
		ft_putnbr_base(nbr, "0123456789abcdef");
	else if (c == 'X')
		ft_putnbr_base(nbr, "0123456789ABCDEF");
	len_nbr = 0;
	if (nbr <= 0)
		len_nbr += 1;
	while (nbr)
	{
		nbr /= base;
		len_nbr += 1;
	}
	return (len_nbr);
}
