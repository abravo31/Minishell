/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:14:51 by motero            #+#    #+#             */
/*   Updated: 2023/01/09 20:34:33 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "structures.h"

int	execute_builtin(t_cmd *cmd)
{
	char const	*builtins[]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int const	(*builtin_functions[])(char **)
		= {&builtin_echo, &builtin_cd, &builtin_pwd, &builtin_export,
		&builtin_unset, &builtin_env, &builtin_exit};
	int			i;
	int const	nbr_builtins = sizeof(builtins) / sizeof(char const *);

	if (!cmd->cmd[0])
		return (EXIT_FAILURE);
	i = 0;
	while (i < nbr_builtins)
	{
		if (ft_strcmp(cmd->cmd[0], builtins[i]) == 0)
			return (cmd->id = BUILTIN, (*builtin_functions[i])(cmd->cmd));
		i++;
	}
	return (execute_external(cmd));
}
