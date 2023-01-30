/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main_garbge_collector.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:12:29 by motero            #+#    #+#             */
/*   Updated: 2023/01/29 18:12:05 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

t_garbage_collector	**singleton_garbage_collector(void)
{
	static t_garbage_collector	*head_gc = NULL;

	return (&head_gc);
}

void	init_garbage_collector(void)
{
	t_garbage_collector	**gc;

	gc = singleton_garbage_collector();
	if (!*gc)
	{
		*gc = malloc(sizeof(t_garbage_collector));
		if (!gc)
			return ;
		(*gc)->ptr = NULL;
	}
}

void	add_to_garbage_collector(void *ptr, t_memory_type type)
{
	t_garbage_collector	**gc;
	t_list				*new;

	gc = singleton_garbage_collector();
	if (!*gc)
		init_garbage_collector();
	if (*gc)
	{
		if (type == INT)
			printf("text passed %s\n", (char *)ptr);
		new = (t_list *)malloc(sizeof(t_list));
		if (!new)
			return ;
		new->content = (t_mem_block *)malloc(sizeof(t_mem_block));
		if (!new->content)
		{
			free(new);
			return ;
		}
		((t_mem_block *)new->content)->ptr = ptr;
		((t_mem_block *)new->content)->type = type;
		ft_lstadd_front(&(*gc)->ptr, new);
	}
}


void	free_garbage_collector(void)
{
	t_garbage_collector	**gc;
	t_list				*tmp;
	t_list				*next;
	t_mem_block			*block;

	gc = singleton_garbage_collector();
	if (!*gc)
		return ;
	tmp = (*gc)->ptr;
	while (tmp)
	{
		printf("erasing something\n");
		next = tmp->next;
		block = (t_mem_block *)tmp->content;
		if (block->type == INT)
			free(block->ptr);
		else if (block->type == D_INT)
			free(block->ptr);
		else if (block->type == ENV)
			free(block->ptr);
		else if (block->type == LST)
			ft_lstclear(block->ptr, free);
		else if (block->type == AST)
			free_ast((t_ast *)block->ptr);
		else if (block->type == CMD)
			ft_lstclear(block->ptr, &free_cmd);
		free(block);
		free(tmp);
		tmp = next;
	}
	free(*gc);
	*gc = NULL;
}
