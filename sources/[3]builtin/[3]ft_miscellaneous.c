/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3]ft_miscellaneous.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/02/03 18:12:10 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "structures.h"

int	builtin_exit(t_minishell *msh, t_ast *root)
{
	char	**cmd;
	int		exit_code;

	(void)msh;
	cmd = root->right->left->arg;
	if (cmd[1] == NULL)
		exit_code = 130;
	else
		exit_code = ft_atoi(cmd[1]) % 256;
	ft_putstr_fd("exit\n", 1);
	free_garbage_collector();
	exit(exit_code);
	return (1);
}
