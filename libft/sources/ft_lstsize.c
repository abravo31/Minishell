/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 23:40:53 by motero            #+#    #+#             */
/*   Updated: 2022/07/20 16:43:31 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_lst *lst)
{
	int	size;

	size = 0;
	if (!lst)
		return (size);
	else
	{
		while (lst)
		{
			lst = lst->next;
			size++;
		}
	}
	return (size);
}
