/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 01:42:12 by motero            #+#    #+#             */
/*   Updated: 2023/01/28 23:28:46 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst)
		return ;
	while (*lst && lst)
	{
		temp = (*lst)->next;
		if (del)
			ft_lstdelone(*lst, del);
		else
			ft_lstdelone(*lst, NULL);
		*lst = temp;
	}
}
