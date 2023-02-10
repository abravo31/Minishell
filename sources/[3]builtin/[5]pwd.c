/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [5]pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/02/08 21:31:42 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(t_minishell *msh, t_ast *root)
{
	char	*path;

	g_status = 0;
	path = getcwd_pwd();
	if (path == NULL)
		return (1);
	add_to_garbage_collector(path, INT);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	(void)msh;
	(void)root;
	g_status = 0;
	return (0);
}

char	*getcwd_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		if (errno == ERANGE)
		{
			free(path);
			errors_messages_cases("pwd: error: path too long", 1);
		}
		else if (errno == EACCES)
			errors_messages_cases("pwd: error: permission denied", 1);
		else if (errno == ENOENT)
			errors_messages_cases("pwd: error: No such File or directory", 1);
		else
			errors_messages_cases(strerror(errno), 1);
	}
	return (path);
}
