/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_switch_case_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:59:23 by motero            #+#    #+#             */
/*   Updated: 2022/06/01 21:48:42 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_percent(void)
{
	ft_putchar('%');
	return (1);
}

char	ft_print_char(char c, const char *str)
{
	char	new_c;

	ft_putchar(c);
	new_c = *str;
	return (new_c);
}
