/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]free_blocks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:36:16 by motero            #+#    #+#             */
/*   Updated: 2023/02/10 20:42:00 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	free_garbage_collector(t_mode mode)
{
	t_garbage_collector	**gc;

	gc = singleton_garbage_collector();
	if (!*gc)
		return ;
	free_all_blocks(*gc, mode);
	if (mode == ALL)
	{
		free(*gc);
		*gc = NULL;
	}
}

void	free_all_blocks(t_garbage_collector *gc, t_mode mode)
{
	t_list	*tmp;
	t_list	*next;
	t_list	*prev;

	prev = NULL;
	tmp = gc->ptr;
	while (tmp)
	{
		next = tmp->next;
		if (mode == ALL || (mode == EXCEPT_ENV
				&& ((t_mem_block *)tmp->content)->type != ENV))
		{
			free_block((t_mem_block *)tmp->content, mode);
			free(tmp);
			if (prev != NULL)
				prev->next = next;
			else
				gc->ptr = next;
		}
		else
			prev = tmp;
		tmp = next;
		if (mode != EXCEPT_ENV)
			gc->ptr = NULL;
	}
}

void	free_block(t_mem_block *block, t_mode mode)
{
	if (block->type == INT)
		free(block->ptr_int.ptr);
	else if (block->type == D_INT)
		free_double_pointer(block->ptr_int.ptr);
	else if (block->type == LST)
		ft_lstclear(block->ptr_int.ptr, &free);
	else if (block->type == AST)
		free_ast((t_ast *)block->ptr_int.ptr);
	else if (block->type == CMD)
		ft_lstclear(block->ptr_int.ptr, &free_cmd);
	else if (block->type == ENV && mode == ALL)
		ft_lstclear(block->ptr_int.ptr, &free_env);
	else if (block->type == FD)
		close_fd(block);
	if (mode == ALL)
		free(block);
	else if (mode == EXCEPT_ENV && block->type != ENV)
		free(block);
}

void	close_fd(t_mem_block *block)
{
	struct stat	buf;

	if (fstat(((int)(block->ptr_int.val)), &buf) == 0
		&& buf.st_nlink > 0)
		close((int)block->ptr_int.val);
}
