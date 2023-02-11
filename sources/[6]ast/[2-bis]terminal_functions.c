/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2-bis]terminal_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:33:40 by motero            #+#    #+#             */
/*   Updated: 2023/02/11 01:34:07 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	builtin_cmd(t_list **head)
{
	t_cmd		*cmd;
	int			i;
	char const	*builtins[7]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int const	nbr_builtins = sizeof(builtins) / sizeof(char const *);

	if ((*head) == NULL)
		return (0);
	cmd = (t_cmd *)(*head)->content;
	i = 0;
	while (i < nbr_builtins)
	{
		if (ft_strcmp(cmd->cmd, builtins[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

/*
This function is used to extract the redirection operator from the
input list and create an AST node for it. It checks if the current
element in the input list is a redirection operator.
*/
t_ast	*cmd_redir(t_list **head, int *i)
{
	t_cmd	*cmd;

	if ((*head) == NULL)
		return (NULL);
	cmd = (t_cmd *)(*head)->content;
	if (is_redirection(cmd))
	{
		(*i)++;
		(*head) = (*head)->next;
		return (create_ast_terminal(cmd, NULL, NULL));
	}
	return (NULL);
}
