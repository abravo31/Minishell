/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]free_blocks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:36:16 by motero            #+#    #+#             */
/*   Updated: 2023/02/05 00:34:57 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	free_garbage_collector(void)
{
	t_garbage_collector	**gc;

	gc = singleton_garbage_collector();
	if (!*gc)
		return ;
	free_all_blocks(*gc);
	free(*gc);
	*gc = NULL;
}

void	free_all_blocks(t_garbage_collector *gc)
{
	t_list	*tmp;
	t_list	*next;

	tmp = gc->ptr;
	while (tmp)
	{
		next = tmp->next;
		free_block((t_mem_block *)tmp->content);
		free(tmp);
		tmp = next;
	}
}

void	free_block(t_mem_block *block)
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
	else if (block->type == ENV)
		ft_lstclear(block->ptr_int.ptr, &free_env);
	else if (block->type == FD)
		close_fd(block);
	free(block);
}

void	close_fd(t_mem_block *block)
{
	struct stat	buf;

	if (fstat(((int)(block->ptr_int.val)), &buf) == 0
		&& buf.st_nlink > 0)
		close((int)block->ptr_int.val);
}
