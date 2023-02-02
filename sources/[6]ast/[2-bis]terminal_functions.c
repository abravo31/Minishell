/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2-bis]terminal_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:33:40 by motero            #+#    #+#             */
/*   Updated: 2023/02/02 22:33:59 by motero           ###   ########.fr       */
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
