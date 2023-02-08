/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3]tild.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo31 <abravo31@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 23:13:34 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/08 14:19:12 by abravo31         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tild(t_minishell *msh, char *str)
{
	char	*new;
	char	*home;
	int		i;
	int		n;

	i = 1;
	n = 0;
	home = get_env_value_build(msh->env, "HOME");
	new = malloc((sizeof (char)) * (ft_strlen(&str[i]) + \
	ft_strlen(home) + 1));
	if (!new)
		return (NULL);
	while (home && home[n])
	{
		new[n] = home[n];
		n++;
	}
	while (str[i])
		new[n++] = str[i++];
	new[n] = '\0';
	free(str);
	return (new);
}

void	check_tild(t_minishell *msh)
{
	t_list	*iter;
	t_cmd	*current;
	t_cmd	*prev;

	iter = msh->cmd;
	current = NULL;
	prev = NULL;
	while (iter)
	{
		current = (t_cmd *) iter->content;
		if (current->cmd && current->cmd[0] == '~' && current->id == WORD && \
		(prev == NULL || prev->space == 1) \
		&& (current->cmd[1] == '/' || current->cmd[1] == '\0'))
			current->cmd = expand_tild(msh, current->cmd);
		prev = (t_cmd *) iter->content;
		iter = iter->next;
	}
}
