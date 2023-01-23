/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:22:07 by motero            #+#    #+#             */
/*   Updated: 2022/11/23 01:25:40 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	abs_num(int n)
{
	if (n < 0)
		return ((unsigned int)-n);
	else
		return ((unsigned int)n);
}

static int	ft_size_num(int num)
{
	int				size;
	unsigned int	nb;

	size = 0;
	nb = abs_num(num);
	while (nb)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

static unsigned int	sign_num(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

char	*ft_itoa(int n)
{
	int				size_num;
	int				i;
	char			*num;
	unsigned int	nb;

	if (n == 0)
		return (ft_strdup("0"));
	size_num = ft_size_num(n);
	num = (char *)malloc(sizeof(char) * (size_num + 1 + sign_num(n)));
	if (!num)
		return (NULL);
	i = 0;
	if (n < 0)
		num[0] = '-';
	nb = abs_num(n);
	while (i < size_num)
	{
		num[size_num - i - 1 + sign_num(n)] = (nb % 10) + '0';
		nb /= 10;
		i++;
	}
	num[size_num + sign_num(n)] = '\0' ;
	return (num);
}

/*int	main()*/
/*{*/
	/*char	*n;*/

	/*n =	ft_itoa(INT_MIN);*/
	/*printf("Number is|%s| len is %ld \n", n, ft_strlen(n));*/
/*}*/
