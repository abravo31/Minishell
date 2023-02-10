/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]ft_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/02/10 23:54:27 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
//env with no options or arguments
int	builtin_env(t_minishell *msh, t_ast *root)
{
	if (msh->env == NULL)
		return (0);
	g_status = 0;
	if (root->right != NULL)
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	print_env(msh->envp);
	(void)root;
	return (0);
}

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] != '\0')
		{
			ft_putstr_fd(envp[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
}
