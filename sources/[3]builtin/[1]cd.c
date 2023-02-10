/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/02/11 00:37:58 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "structures.h"

int	builtin_cd(t_minishell *msh, t_ast *root)
{
	g_status = 0;
	if (root->right == NULL)
		new_path_empty(msh);
	else if (root->right)
	{
		if (root->right->left->arg[2] != NULL)
			error_messages_default_cases("cd: error: too many arguments", 1);
		else
			new_path_normal(msh, root);
	}
	(void)msh;
	return (0);
}

char	*getcwd_until_path_fits(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		if (errno == ERANGE)
		{
			free(path);
			error_messages_default_cases("cd: error: path too long", 1);
		}
		else if (errno == EACCES)
			error_messages_default_cases("cd: error: permission denied", 1);
		else if (errno == ENOENT)
			error_messages_default_cases("cd: error: No such File or directory", 1);
		else
			error_messages_default_cases(strerror(errno), 1);
	}
	return (path);
}

void	if_chdir(t_minishell *msh, char *path)
{
	path = getcwd_until_path_fits();
	if (path == NULL)
		return (error_messages_default_cases("cd: error: unknown error", 1));
	add_to_garbage_collector(path, INT);
	modify_env_value(msh->env, "PWD", path);
}

void	new_path_empty(t_minishell *msh)
{
	char	*home;

	home = get_env_value_build(msh->env, "HOME");
	if (home == NULL)
		error_messages_default_cases("cd: error: HOME not set", 1);
	else
	{
		if (chdir(home) == -1)
		{
			if (errno == EACCES)
				error_messages_default_cases("cd: error: permission denied", 1);
			else if (errno == ENOENT)
				error_messages_default_cases("cd: error: no such file \
				or directory", 1);
			else
				error_messages_default_cases("cd: error: unknown error", 1);
		}
		else
			if_chdir(msh, NULL);
	}
}

void	new_path_normal(t_minishell *msh, t_ast *root)
{
	char	*path;

	if (chdir(root->right->left->arg[1]) == -1)
	{
		if (errno == EACCES)
			error_messages_default_cases("cd: error: permission denied", 1);
		else if (errno == ENOENT)
			error_messages_default_cases("cd: error: no such file or directory", 1);
		else
			error_messages_default_cases("cd: error: unknown error", 1);
	}
	else
	{
		path = getcwd_until_path_fits();
		if (path == NULL)
			return ;
		add_to_garbage_collector(path, INT);
		modify_env_value(msh->env, "PWD", path);
	}
}
