/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2-c]export_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo31 <abravo31@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:10:44 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/07 16:09:06 by abravo31         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_export(const char *env)
{
	int		i;

	i = 0;
	if (env[i] == '=')
	{
		printf("-minishell: export: `=': not a valid identifier\n");
		return (0);
	}
	if (ft_isdigit(env[i]) == 1)
	{
		printf("-minishell: export: `%s': not a valid identifier\n", env);
		return (0);
	}
	while (env[i] && env[i] != '=')
	{
		while (env[i] == '_')
			i++;
		if (ft_isalnum(env[i]) == 0)
		{
			printf("-minishell: export: `%s': not a valid identifier\n", env);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	if (*tab == NULL)
		return ;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

int	str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
