/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/02/09 00:25:12 by motero           ###   ########.fr       */
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
			errors_messages_cases("cd: error: too many arguments", 1);
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
			errors_messages_cases("cd: error: path too long", 1);
		}
		else if (errno == EACCES)
			errors_messages_cases("cd: error: permission denied", 1);
		else if (errno == ENOENT)
			errors_messages_cases("cd: error: No such File or directory", 1);
		else
			errors_messages_cases(strerror(errno), 1);
	}
	return (path);
}

void	new_path_empty(t_minishell *msh)
{
	char	*home;
	char	*path;

	home = get_env_value_build(msh->env, "HOME");
	if (home == NULL)
		errors_messages_cases("cd: error: HOME not set", 1);
	else
	{
		if (chdir(home) == -1)
		{
			if (errno == EACCES)
				errors_messages_cases("cd: error: permission denied", 1);
			else if (errno == ENOENT)
				errors_messages_cases("cd: error: no such file or directory", 1);
			else
				errors_messages_cases("cd: error: unknown error", 1);
		}
		else
		{	
			path = getcwd_until_path_fits();
			if (path == NULL)
				return (errors_messages_cases("cd: error: unknown error", 1));
			add_to_garbage_collector(path, INT);
			modify_env_value(msh->env, "PWD", path);
		}
	}
}

void	new_path_normal(t_minishell *msh, t_ast *root)
{
	char	*path;

	if (chdir(root->right->left->arg[1]) == -1)
	{
		if (errno == EACCES)
			errors_messages_cases("cd: error: permission denied", 1);
		else if (errno == ENOENT)
			errors_messages_cases("cd: error: no such file or directory", 1);
		else
			errors_messages_cases("cd: error: unknown error", 1);
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
