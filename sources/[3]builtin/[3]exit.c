/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3]exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/02/03 20:47:50 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "structures.h"

int	builtin_exit(t_minishell *msh, t_ast *root)
{
	char	**cmd;
	int		exit_code;

	(void)msh;
	cmd = NULL;
	if (root->right)
	{
		cmd = root->right->left->arg;
		exit_code = ft_atoi(cmd[1]) % 256;
	}
	else
		exit_code = 130;
	ft_putstr_fd("exit\n", 1);
	free_garbage_collector();
	exit(exit_code);
	return (1);
}
