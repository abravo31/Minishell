/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [10]env_manipulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 23:48:31 by motero            #+#    #+#             */
/*   Updated: 2023/02/10 21:11:15 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_env_value_build(t_list *env, char *key)
{
	t_env	*env_var;
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		env_var = tmp->content;
		if (ft_strcmp(env_var->key, key) == 1)
			return (env_var->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	modify_env_value(t_list *env, char *key, char *value)
{
	t_env	*env_var;
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		env_var = tmp->content;
		if (ft_strcmp(env_var->key, key) == 1)
		{
			free(env_var->value);
			env_var->value = ft_strdup(value);
			if (env_var->value == NULL)
				error_safe_exit("cd: error: unknown error", 1);
			return ;
		}
		tmp = tmp->next;
	}
}

void	list_env_to_char_env(t_minishell *msh)
{
	t_list	*tmp;
	t_env	*env_var;
	char	*buffer;
	char	**env_char;
	int		i;

	i = 0;
	env_char = malloc(sizeof(char *) * (ft_lstsize(msh->env) + 1));
	if (env_char == NULL)
		error_safe_exit("cd: error: unknown error", 1);
	msh->envp = env_char;
	add_to_garbage_collector(msh->envp, D_INT);
	tmp = msh->env;
	while (tmp)
	{
		env_var = tmp->content;
		if (env_var && env_var->key != NULL)
		{
			buffer = ft_strjoin(env_var->key, "=");
			if (buffer == NULL)
				return ;
			msh->envp[i] = ft_strjoin(buffer, env_var->value);
			free(buffer);
			if (msh->envp[i] == NULL)
				return ;
		}
		else
		{	
			msh->envp[i] = ft_strdup("");
			if (msh->envp[i] == NULL)
				error_safe_exit("error: unknown error", 1);
		}
		tmp = tmp->next;
		i++;
	}
	msh->envp[i] = NULL;
}
