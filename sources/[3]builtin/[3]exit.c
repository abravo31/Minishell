/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3]exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/02/11 16:43:23 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/* errors to check  : 1) too many arguments 2) argument is not a number 
** 3) argument is a number but biger than LLONG_MAX
*/
int	builtin_exit(t_minishell *msh, t_ast *root)
{
	char		**cmd;
	long long	exit_code;

	(void)msh;
	g_status = 0;
	exit_code = 0;
	cmd = NULL;
	ft_putstr_fd("exit\n", 1);
	if (root->right)
	{
		cmd = root->right->left->arg;
		if ((is_numeric(cmd[1]) == 0)
			|| !is_big_number(ft_atoll(cmd[1]), cmd[1]))
			return (error_messages_default_cases("numeric argument require"
					"d", 1), exit_code = 2, 1);
		else if (cmd[2] != NULL)
		{
			error_messages_default_cases("exit: too many arguments", 1);
			return (exit_code = 1, 1);
		}
		else
			exit_code = transform_exit_code(cmd[1]);
	}
	free_garbage_collector(ALL);
	return (exit(exit_code), 1);
}

long long	transform_exit_code(char *cmd)
{
	long long	exit_code;

	exit_code = ft_atoll(cmd) % 256;
	if (exit_code < 0)
		exit_code += 256;
	return (exit_code);
}
