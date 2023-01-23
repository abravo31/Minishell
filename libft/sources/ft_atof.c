/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:52:08 by motero            #+#    #+#             */
/*   Updated: 2022/10/30 00:28:57 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *nptr)
{
	double	a;
	char	**str;
	double	dec;
	int		sign;
	int		i;

	sign = 1;
	if (nptr[0] == '-')
		sign = -1;
	dec = 0;
	a = 0.0;
	str = ft_split(nptr, '.');
	a += (double)ft_atoi(str[0]);
	if (ft_strlen(str[1]))
		dec = (double)ft_atoi(str[1]) * (double)pow(10, -1
				* (double)ft_strlen(str[1]));
	a += dec;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	if ((double)sign * a > 0)
		return (a);
	else
		return (-a);
}
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int val;
	char strn1[] = "\t\n\r\v\f  469 \n";

	val = ft_atoi(strn1);
	printf("String value = %s\n", strn1);
	printf("Integer value = %d\n", val);

	char strn2[] = "\n\n\n    -46\b9 \n5d6";
	val = ft_atoi(strn2);
	printf("String value = %s\n", strn2);
	printf("Integer value = %d\n", val);

	return (0);
}*/
