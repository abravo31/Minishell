/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:23:42 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/08 19:53:51 by motero           ###   ########.fr       */
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

void	ft_join_pop(t_list *cur, t_list *rmv)
{
	t_cmd	*cmd;
	t_cmd	*cmd_next;

	cmd = (t_cmd *)cur->content;
	cmd_next = (t_cmd *)rmv->content;
	cmd->cmd = ft_strjoin_cmd(cmd->cmd, cmd_next->cmd);
	cmd->space = cmd_next->space;
	cur->next = cur->next->next;
	free(rmv->content);
	free(rmv);
}

void	ft_dup_list(t_minishell *msh)
{
	t_list	*new;
	t_list	*list;
	t_cmd	*cmd;
	int		i;
	char	*dup_char;

	list = msh->cmd;
	i = 0;
	while (list)
	{
		cmd = (t_cmd *)list->content;
		dup_char = ft_strdup(cmd->cmd);
		if (!dup_char)
		{
			free_garbage_collector(ALL);
			printf("error while duplicating a delimitor\n");
			return ;
		}
		new = ft_lstnew((void *)new_cmd(dup_char, cmd->id, cmd->space));
		if (i == 0)
		{
			msh->cmd_expand = new;
			add_to_garbage_collector((void *)&msh->cmd_expand, CMD);
		}
		else
			ft_lstadd_back(&msh->cmd_expand, new);
		list = list->next;
		i++;
	}
}

int	ft_should_join(t_cmd *cmd, t_cmd *cmd_next)
{
	if ((cmd->id >= D_QUOTE && cmd->id <= WORD) && \
	(cmd_next->id >= D_QUOTE && cmd_next->id <= WORD) && cmd->space == 0)
		return (1);
	return (0);
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
		if (ft_should_join(cmd, cmd_next))
			ft_join_pop(list, list->next);
		if (cmd->id >= D_QUOTE && cmd->id < WORD)
			cmd->id = WORD;
		if (list->next)
			cmd_next = (t_cmd *)list->next->content;
		if (list->next && !ft_should_join(cmd, cmd_next))
			list = list->next;
	}
	if (list)
	{
		cmd = (t_cmd *)list->content;
		if (cmd->id >= D_QUOTE && cmd->id < WORD)
			cmd->id = WORD;
	}
}
