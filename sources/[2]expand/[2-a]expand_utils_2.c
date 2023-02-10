/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2-a]expand_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:16:18 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/10 22:52:43 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lenof(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = (n < 0);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_stoval(t_minishell *msh, int n)
{
	int				i;
	int				len;
	unsigned int	nb;

	nb = -(n < 0) * (n) + (n > 0) * (n);
	i = (n < 0);
	len = lenof(n);
	if (n < 0)
		msh->value[0] = '-';
	msh->value[len] = 0;
	while (--len >= i)
	{
		msh->value[len] = (nb % 10) + '0';
		nb /= 10;
	}
}

char	*ft_get_status(t_minishell *msh, int *n, int *i)
{
	*n += lenof(g_status);
	*i += 1;
	ft_stoval(msh, g_status);
	return (msh->value);
}
