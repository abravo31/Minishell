/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0-a]env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:29:23 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/10 22:50:48 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(char **env, t_minishell *msh)
{
	int		i;
	int		flag;

	i = -1;
	if (!env[0])
	{
		initilialize_emtpy_env(msh);
		return ;
	}
	flag = 1;
	while (env[++i] && flag)
		flag = env_iter(msh, env[i], 0, 0);
	if (!flag)
		error_safe_exit("Alloc eror : env_iter", 1);
	increment_shlvl(msh);
}

//initialzie emtpy env with pwd and SHLVL at  launch if env empty
void	initilialize_emtpy_env(t_minishell *msh)
{
	t_list	*new;
	t_env	*temp;
	char	*pwd;

	pwd = getcwd_until_path_fits();
	if (pwd == NULL)
		return (error_safe_exit("pwd: error: unknown error", 1));
	temp = new_env(ft_strdup("PWD"), pwd);
	if (temp == NULL)
		return ;
	new = ft_lstnew((void *)temp);
	if (new == NULL)
		return (free_env(temp), error_message("malloc error", 1));
	msh->env = new;
	add_to_garbage_collector((void *)&msh->env, ENV);
	create_add_shlvl(msh);
}

void	increment_shlvl(t_minishell *msh)
{
	t_list	*current;
	t_env	*env;
	int		shlvl;

	current = msh->env;
	env = NULL;
	shlvl = 0;
	while (current)
	{
		env = (t_env *) current->content;
		if (env && ft_strcmp(env->key, "SHLVL") == 1)
		{
			shlvl = ft_atoi(env->value);
			shlvl++;
			free(env->value);
			env->value = ft_itoa(shlvl);
			if (env->value == NULL)
				break ;
			return ;
		}
		current = current->next;
	}
	create_add_shlvl(msh);
}

void	create_add_shlvl(t_minishell *msh)
{
	t_list	*new;
	t_env	*temp;

	temp = new_env(ft_strdup("SHLVL"), ft_strdup("1"));
	if (temp == NULL)
		return (error_message("malloc error", 1));
	new = ft_lstnew((void *)temp);
	if (new == NULL)
		return (free_env(temp), error_message("malloc error", 1));
	ft_lstadd_back(&msh->env, new);
}
