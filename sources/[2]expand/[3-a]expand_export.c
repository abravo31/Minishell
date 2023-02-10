/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3-a]expand_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:55:51 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/10 23:20:21 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_is_zero(t_cmd *cur, char *insert)
{
	free(cur->cmd);
	cur->cmd = ft_strdup(insert);
	if (cur->cmd == NULL)
		error_safe_exit("Malloc failed", 1);
	cur->space = 1;
}

void	insert_to_list(int i, char *insert, t_list **iter)
{
	t_cmd	*cur;
	t_cmd	*cmd_new;
	t_list	*new;

	cur = (t_cmd *)((*iter)->content);
	cmd_new = NULL;
	if (i == 0)
	{
		if_is_zero(cur, insert);
		return ;
	}
	cmd_new = new_cmd(ft_strdup(insert), WORD, 1);
	if (cmd_new == NULL)
		error_safe_exit("Malloc failed", 1);
	new = ft_lstnew(cmd_new);
	if (new == NULL)
		error_safe_exit("Malloc failed", 1);
	if (*iter == NULL)
	{
		*iter = new;
		return ;
	}
	new->next = (*iter)->next;
	(*iter)->next = new;
	*iter = (*iter)->next;
}
