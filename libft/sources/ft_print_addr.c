/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:59:55 by motero            #+#    #+#             */
/*   Updated: 2022/06/01 20:31:44 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_addr(unsigned long addr)
{
	int	size;

	size = 0;
	while (addr)
	{
		addr /= 16;
		size++;
	}
	return (size);
}

int	ft_print_addr(unsigned long addr)
{
	char	*base;
	char	*buffer;
	int		i;
	int		len;

	base = "0123456789abcdef";
	i = 0;
	len = ft_len_addr(addr);
	buffer = malloc(sizeof(char) * (len + 2 + 1));
	if (!buffer)
		return (0);
	while (addr != '\0')
	{
		buffer [i++] = base[addr % 16];
		addr /= 16;
	}
	buffer[i++] = 'x';
	buffer[i] = '0';
	while (i + 1)
		ft_putchar(buffer[i--]);
	free(buffer);
	return (len);
}
