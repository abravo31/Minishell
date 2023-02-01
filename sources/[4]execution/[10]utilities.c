/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [10]utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:30:10 by motero            #+#    #+#             */
/*   Updated: 2023/01/31 19:23:55 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* Checks for acces of Cmd in path
** We test at first if the path is included in the cmd (/,.,~)
** if not thenm cincatenate each path in env with the cmd and 
** check for access
** Finally When acess is correct we send corresponding PATH so it can be executed
*/
char	*ft_check_access(t_minishell *msh, t_ast *root)
{
	char	*cmd;
	char	*path;
	size_t	i;

	cmd = root->data;
	msh->path = ft_parse_path(msh->envp);
	if (!msh->path)
		error_safe_exit("error at checkin access\n");
	add_to_garbage_collector(msh->path, D_INT);
	if (cmd[0] == '/' || cmd[0] == '.' || cmd[0] == '~')
	{
		path = cmd;
		if (!(access(path, (X_OK))))
			return (path);
	}
	else
	{
		i = 0;
		while (msh->path[i])
		{
			path = ft_strjoin(msh->path[i++], cmd);
			if (!path)
				error_safe_exit("error at checkin access\n");
			add_to_garbage_collector(path, INT);
			if (!(access(path, (X_OK))))
				return (path);
		}
	}
	return (NULL);
}

/** PARSING OF EAACH PATH CONTAINED IN ENV BEFORE CHECKING ACCESS OF COMMANDS**
** 1- look up for line containt PATH and extracting that str **
** 2- Extracting the line without PATH and spliting it by ':' character**
** */
char	**ft_parse_path(char **env)
{
	char	*paths;
	char	**paths_split;
	size_t	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
	{
		paths_split = malloc(sizeof(char *));
		return (paths_split[0] = 0, paths_split);
	}
	paths = malloc(sizeof(char) * (ft_strlen(env[i]) - 4));
	ft_strlcpy(paths, env[i] + 5, ft_strlen(env[i]) - 5);
	paths_split = ft_split(paths, ':');
	free(paths);
	if (!paths_split)
	{
		ft_putstr_fd("Error: No environement PATH found\n", STDERR_FILENO);
		return (NULL);
	}
	i = -1;
	while (paths_split[++i])
		paths_split[i] = ft_strconcat(paths_split[i], "/");
	return (paths_split);
}
