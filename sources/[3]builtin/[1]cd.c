/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/02/05 00:18:28 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "structures.h"

int	builtin_cd(t_minishell *msh, t_ast *root)
{
	if (root->right == NULL)
		new_path_empty(msh);
	else if (root->right)
	{
		if (root->right->left->arg[2] != NULL)
			error_safe_exit("cd: error: too many arguments");
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
	ft_putstr_fd("actual path ", 1);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	if (path == NULL)
	{
		if (errno == ERANGE)
		{
			free(path);
			error_safe_exit("cd: error: path too long");
		}
		else if (errno == EACCES)
			error_safe_exit("cd: error: permission denied");
		else if (errno == ENOENT)
			error_safe_exit("cd: error: no such file or directory");
		else
			error_safe_exit("cd: error: unknown error");
	}
	return (path);
}

void	new_path_empty(t_minishell *msh)
{
	char	*home;
	char	*path;

	home = get_env_value(msh->env, "HOME");
	if (home == NULL)
		error_safe_exit("cd: error: HOME not set");
	else
	{
		if (chdir(home) == -1)
		{
			if (errno == EACCES)
				error_safe_exit("cd: error: permission denied");
			else if (errno == ENOENT)
				error_safe_exit("cd: error: no such file or directory");
			else
				error_safe_exit("cd: error: unknown error");
		}
		else
		{	
			path = getcwd_until_path_fits();
			if (path == NULL)
				return (error_safe_exit("cd: error: unknown error"));
			add_to_garbage_collector(path, INT);
			modify_env_value(msh->env, "PWD", path);
			ft_putstr_fd("new path : ", 1);
			ft_putstr_fd(path, 1);
			ft_putstr_fd("\n", 1);
		}
	}
}

void	new_path_normal(t_minishell *msh, t_ast *root)
{
	char	*path;

	if (chdir(root->right->left->arg[1]) == -1)
	{
		if (errno == EACCES)
			error_safe_exit("cd: error: permission denied");
		else if (errno == ENOENT)
			error_safe_exit("cd: error: no such file or directory");
		else
			error_safe_exit("cd: error: unknown error");
	}
	else
	{
		path = getcwd_until_path_fits();
		if (path == NULL)
			return (error_safe_exit("cd: error: unknown error"));
		add_to_garbage_collector(path, INT);
		modify_env_value(msh->env, "PWD", path);
		ft_putstr_fd("new path : ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
}
