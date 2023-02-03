/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3]exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/02/03 23:42:58 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

long long	transform_exit_code(char *cmd);

/* errors to check  : 1) too many arguments 2) argument is not a number 
** 3) argument is a number but biger than LLONG_MAX
*/
int	builtin_exit(t_minishell *msh, t_ast *root)
{
	char		**cmd;
	long long	exit_code;

	(void)msh;
	cmd = NULL;
	if (root->right)
	{
		cmd = root->right->left->arg;
		if (is_numeric(cmd[1]) == 0
			|| !is_big_number(ft_atoll(cmd[1]), cmd[1]))
			exit_code = 2;
		else if (cmd[2] != NULL)
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("exit: too many arguments\n", 2);
			exit_code = 1;
			return (1);
		}
		else
			exit_code = transform_exit_code(cmd[1]);
	}
	else
		exit_code = 130;
	free_garbage_collector();
	exit(exit_code);
	return (1);
}

long long	transform_exit_code(char *cmd)
{
	long long	exit_code;

	exit_code = ft_atoll(cmd) % 256;
	if (exit_code < 0)
		exit_code += 256;
	return (exit_code);
}
