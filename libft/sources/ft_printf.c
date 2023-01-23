/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 16:06:05 by motero            #+#    #+#             */
/*   Updated: 2022/06/01 21:54:30 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

	//%c a single char
	//%s a strng of char
	//%p the void arg pointer, displayed in HEX
	//%d putnumbr 10.0 in base 10
	//%i full number in base 10
	//%u unsigned number i base  10
	//%x hexnm with lowercase
	//%X hex nm with upper case
	//%% percent

int	ft_printf(const char *s, ...)
{
	va_list			args;
	char			c;
	int				len_print;

	va_start(args, s);
	len_print = 0;
	c = *s;
	while (c)
	{
		(void)s++;
		if (c == '%')
		{
			c = *s;
			len_print += ft_flags(args, c);
			c = *++s;
		}
		else
		{
			c = ft_print_char(c, s);
			len_print++;
		}
	}
	va_end(args);
	return (len_print);
}

int	ft_flags(va_list args, char c)
{
	int	len_print;

	len_print = 0;
	if (c == 'c')
		len_print += ft_single_char(va_arg(args, int));
	else if (c == 's')
		len_print += ft_string((char *)va_arg(args, char *));
	else if (c == 'p')
		len_print += ft_address((unsigned long)va_arg(args, const char *));
	else if (c == 'd' || c == 'i')
		len_print += ft_nbr_signed((int)va_arg(args, int));
	else if (c == 'x' || c == 'X' || c == 'u')
		len_print += ft_nbr_unsigned(c, va_arg(args, unsigned int));
	else if (c == '%')
		len_print += ft_percent();
	return (len_print);
}

/*int	main()*/
/*{*/
	/*int j;*/
	/*int k;*/

	/*j = printf("%c  ", 'c');*/
	/*printf("\n===========================\n");*/
	/*k = ft_printf("%c  ", 'c');*/
	/*printf("\ndiff  j |%d| & k |%d|, diff is |%d|\n", j, k, j-k);*/
	/*if (j == k)*/
		/*printf("Vie les maries\n");*/
	/*else*/
		/*printf("c'est le divorce");*/
	/*//printf("|%s|", "");*/
/*}*/
