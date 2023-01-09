/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]builtin_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:14:51 by motero            #+#    #+#             */
/*   Updated: 2023/01/09 23:29:24 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "structures.h"

int	execute_external(t_cmd *cmd)
{
	(void)cmd;
	return (printf("Execute external\n"));
}

void static	init_builtin_functions(int (**builtin_functions)(t_cmd *))
{
	builtin_functions[0] = &builtin_echo;
	builtin_functions[1] = &builtin_cd;
	builtin_functions[2] = &builtin_pwd;
	builtin_functions[3] = &builtin_export;
	builtin_functions[4] = &builtin_unset;
	builtin_functions[5] = &builtin_env;
	builtin_functions[6] = &builtin_exit;
}

int	execute_builtin(t_cmd *cmd)
{
	char const	*builtins[7]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			(*builtin_functions[7])(t_cmd *);
	int const	nbr_builtins = sizeof(builtins) / sizeof(char const *);
	int			i;

	if (!cmd->cmd[0])
		return (EXIT_FAILURE);
	init_builtin_functions(builtin_functions);
	i = 0;
	while (i < nbr_builtins)
	{
		if (ft_strcmp(&cmd->cmd[0], builtins[i]) == 0)
			return (cmd->id = BUILTIN, (*builtin_functions[i])(cmd));
		i++;
	}
	return (execute_external(cmd));
}
