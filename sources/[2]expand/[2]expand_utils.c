/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo31 <abravo31@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:23:42 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/05 21:05:08 by abravo31         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->key = key;
	elem->value = value;
	return (elem);
}

void	ft_pop_list(t_list **begin_list, t_list *cur, t_list *rmv, t_list *prev)
{
	t_list	*tmp;

	while (cur)
	{
		if (cur == rmv)
		{
			if (prev == NULL)
			{
				tmp = *begin_list;
				*begin_list = (*begin_list)->next;
				free(tmp);
			}
			else
			{
				tmp = cur->next;
				prev->next = cur->next;
				free(cur);
			}
			cur = tmp;
		}
		prev = cur;
		if (cur)
			cur = cur->next;
	}
}

// void	ft_add_to_list(t_minishell *msh, char *cmd, int id)
// {
// 	t_list	*new;

// 	new = ft_lstnew((void *)new_cmd(cmd, id, 0));
// 	if (!new)
// 	{
// 		free_garbage_collector();
// 		printf("error while adding a delimitor, 
//		still not error or way toe xit this function!\n");
// 		return ;
// 	}
// 	ft_lstadd_back(&msh->cmd_expand, new);
// }

void	ft_dup_list(t_minishell *msh)
{
	t_list	*new;
	t_list	*list;
	t_cmd	*cmd;

	list = msh->cmd;
	while (list)
	{
		cmd = (t_cmd *)list->content;
		new = ft_lstnew((void *)new_cmd(cmd->cmd, cmd->id, cmd->space));
		ft_lstadd_back(&msh->cmd_expand, new);
		list = list->next;
	}
}

void	join_elems(t_list *list, t_cmd *cmd, t_cmd *cmd_next)
{
	if ((cmd->id >= D_QUOTE && cmd->id <= WORD) && \
	(cmd_next->id >= D_QUOTE && cmd_next->id <= WORD) && cmd->space == 0)
	{
		while ((cmd->id >= D_QUOTE && cmd->id <= WORD) && \
		(cmd_next->id >= D_QUOTE && cmd_next->id <= WORD) && \
		cmd->space == 0 && cmd_next->space == 0 && list->next)
		{
			cmd->cmd = ft_strjoin_cmd(cmd->cmd, cmd_next->cmd);
			ft_pop_list(&list, list, list->next, NULL);
			if (list->next)
				cmd_next = (t_cmd *)list->next->content;
		}
		if ((cmd->id >= D_QUOTE && cmd->id <= WORD) && \
		(cmd_next->id >= D_QUOTE && cmd_next->id <= WORD) && list->next)
		{
			cmd->cmd = ft_strjoin_cmd(cmd->cmd, cmd_next->cmd);
			ft_pop_list(&list, list, list->next, NULL);
		}
	}
}

void	ft_join_quote(t_minishell *msh)
{
	t_list	*list;
	t_cmd	*cmd;
	t_cmd	*cmd_next;

	list = msh->cmd_expand;
	while (list && list->next)
	{
		cmd = (t_cmd *)list->content;
		cmd_next = (t_cmd *)list->next->content;
		join_elems(list, cmd, cmd_next);
		if (cmd->id >= D_QUOTE && cmd->id < WORD)
			cmd->id = WORD;
		list = list->next;
	}
	if (list)
	{
		cmd = (t_cmd *)list->content;
		if (cmd->id >= D_QUOTE && cmd->id < WORD)
			cmd->id = WORD;
	}
}
