/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:45:38 by motero            #+#    #+#             */
/*   Updated: 2022/07/20 16:43:28 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst	*list;

	list = (t_lst *)malloc(sizeof(t_lst));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
