/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2-c]export_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:10:44 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/11 01:32:45 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_iter_bef_equal(const char *env, char *tmp)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=' && env[i] != '+')
	{
		while (env[i] == '_')
			i++;
		if (ft_isalnum(env[i]) == 0 && env[i] != '=' && \
		!(env[i] == '+' && env[i + 1] && env[i + 1] == '='))
		{
			tmp = compose_error_message("minishell: export: `", (char *)env, "':\
			not a valid identifier");
			error_messages_default_cases(tmp, 501);
			return (0);
		}
		i++;
	}
	if (env[i] == '+' && env[i + 1] != '=')
		return (errors_messages_cases("export: not a valid identifier",
				501), 0);
	return (1);
}

int	is_valid_export(const char *env)
{
	int		i;
	char	*tmp;

	i = 0;
	if (env[i] == '=' || env[i] == '+')
	{
		error_messages_default_cases("export: '=':", 501);
		return (0);
	}
	if (ft_isdigit(env[i]) == 1)
	{
		tmp = compose_error_message("minishell: export: `", (char *)env, "':\
		not a valid identifier");
		error_messages_default_cases(tmp, 502);
		return (0);
	}
	if (!env_iter_bef_equal(env, NULL))
		return (0);
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
