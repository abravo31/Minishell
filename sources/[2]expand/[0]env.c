/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo31 <abravo31@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:29:23 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/05 02:32:54 by abravo31         ###   ########.fr       */
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

t_env	*new_env(char *key, char *value)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->key = key;
	elem->value = value;
	return (elem);
}

char	*str_from_range(char *env, int start, int size)
{
	char	*str;
	int		i;

	i = -1;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	while (++i < size)
		str[i] = env[start + i];
	str[i] = '\0';
	return (str);
}

void	get_env(char **env, t_minishell *msh, int i, int k)
{
	int		j;
	char	*key;
	char	*value;

	if (!env)
		ft_lstadd_back(&msh->env, ft_lstnew((void *)new_env(NULL, NULL)));
	while (env[++i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		key = str_from_range(env[i], 0, j);
		if (!key)
			return ;
		k = 0;
		j++;
		while (env[i][j + k])
			k++;
		value = str_from_range(env[i], j, k);
		if (!value)
			return ;
		ft_lstadd_back(&msh->env, ft_lstnew((void *)new_env(key, value)));
	}
}
