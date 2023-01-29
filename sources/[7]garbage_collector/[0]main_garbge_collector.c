/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main_garbge_collector.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:12:29 by motero            #+#    #+#             */
/*   Updated: 2023/01/29 00:21:52 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

t_garbage_collector	*singleton_garbage_collector(void)
{
	static t_garbage_collector	*head_gc = NULL;

	return (head_gc);
}

void	init_garbage_collector(t_memory_type type)
{
	t_garbage_collector	*gc;

	gc = singleton_garbage_collector();
	if (!gc)
	{
		gc = malloc(sizeof(t_garbage_collector));
		if (!gc)
			return ;
		gc->ptr = NULL;
	}
}

void	add_to_garbage_collector(void *ptr, t_memory_type type)
{
	t_garbage_collector	*gc;
	t_list				*new;

	gc = singleton_garbage_collector();
	if (!gc)
		init_garbage_collector(type);
	if (gc)
	{
		new = (t_list *)malloc(sizeof(t_list));
		if (!new)
			return ;
		new->content = (t_mem_block *)malloc(sizeof(t_mem_block));
		if (!new->content)
		{
			free(new->content);
			return ;
		}
		((t_mem_block *)new->content)->ptr = ptr;
		((t_mem_block *)new->content)->type = type;
		ft_lstadd_front(&gc->ptr, new);
	}
}

void	free_garbage_collector(void)
{
	t_garbage_collector	*gc;

	gc = singleton_garbage_collector();
	if (gc)
	{
		ft_lstclear(&gc->ptr, free);
		gc->ptr = NULL;
	}
}
