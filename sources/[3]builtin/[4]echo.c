/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [4]echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/02/03 20:54:36 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_echo(t_minishell *msh, t_ast *root)
{
	int		flag;
	int		i;
	char	**cmd;

	(void)msh;
	g_status = 0;
	if (root->right == NULL)
		return (ft_putstr_fd("\n", 1), 1);
	cmd = root->right->left->arg;
	flag = 0;
	i = 1;
	while (cmd[i] != NULL && is_flag(cmd[i]))
	{
		flag = 1;
		i++;
	}
	while (cmd[i] != NULL)
	{	
		ft_putstr_fd(cmd[i++], 1);
		if (cmd[i] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
	return (1);
}

int	is_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-' || str[i + 1] == '\0' || str[i] == 0)
		return (0);
	i++;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
