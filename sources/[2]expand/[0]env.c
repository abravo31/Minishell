/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:29:23 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/09 04:02:34 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	__debug_env(t_minishell *msh)
// {
// 	t_list	*iter;
// 	t_env	*current;

// 	iter = msh->env;
// 	current = NULL;
// 	while (iter)
// 	{
// 		current = (t_env *) iter->content;
// 		printf("(%s){%s}\n", current->key, current->value);
// 		iter = iter->next;
// 	}
// }

char	*get_value_from_key(t_minishell *msh, char *key)
{
	t_list	**temp;
	t_env	*temp2;

	temp = &msh->env;
	temp2 = NULL;
	while (*temp)
	{	
		temp2 = (t_env *)(*temp)->content;
		if (ft_strcmp(key, temp2->key))
			return (temp2->value);
		*temp = (*temp)->next;
	}
	return (NULL);
}

char	*get_env_value(int *index, t_minishell *msh, char *str)
{	
	int		len;
	t_list	*head;
	char	*value;

	len = ft_strlen(str);
	*index += len;
	head = msh->env;
	value = get_value_from_key(msh, str);
	msh->env = head;
	return (value);
}

char	*str_from_range(char *env, int start, int size)
{
	char	*str;
	int		i;

	i = -1;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		error_safe_exit("Malloc failed", 1);
	while (++i < size)
		str[i] = env[start + i];
	str[i] = '\0';
	return (str);
}

void	env_iter(t_minishell *msh, char *env, int j, int k)
{
	char	*key;
	char	*value;
	t_list	*new;

	while (env[j] != '=')
		j++;
	key = str_from_range(env, 0, j++);
	if (!key)
		return ;
	while (env[j + k])
		k++;
	value = str_from_range(env, j, k);
	if (!value)
		return ;
	if (msh->env == NULL)
	{
		new = ft_lstnew((void *)new_env(key, value));
		if (new == NULL)
			error_safe_exit("malloc error", 1);
		msh->env = new;
		add_to_garbage_collector((void *)&msh->env, ENV);
	}
	else
		ft_lstadd_back(&msh->env, ft_lstnew((void *)new_env(key, value)));
}

void	get_env(char **env, t_minishell *msh)
{
	int		i;

	i = -1;
	if (!env[0])
	{
		initilialize_emtpy_env(msh);
		return ;
	}
	while (env[++i])
		env_iter(msh, env[i], 0, 0);
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
		error_safe_exit("malloc error", 1);
	new = ft_lstnew((void *)temp);
	if (new == NULL)
		error_safe_exit("malloc error", 1);
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
		if (ft_strcmp(env->key, "SHLVL") == 1)
		{
			shlvl = ft_atoi(env->value);
			shlvl++;
			free(env->value);
			env->value = ft_itoa(shlvl);
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
		error_safe_exit("malloc error", 1);
	new = ft_lstnew((void *)temp);
	if (new == NULL)
		error_safe_exit("malloc error", 1);
	ft_lstadd_back(&msh->env, new);
}
