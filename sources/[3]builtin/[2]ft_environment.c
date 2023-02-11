/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]ft_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/02/11 17:12:32 by motero           ###   ########.fr       */
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
		error_messages_default_cases("env : too many arguments", 2);
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
