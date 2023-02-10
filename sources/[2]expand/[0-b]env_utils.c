/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0-b]env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:29:23 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/10 23:55:24 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!env)
		return (NULL);
	i = -1;
	str = malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	while (++i < size)
		str[i] = env[start + i];
	str[i] = '\0';
	return (str);
}

void	handle_env_null(t_minishell *msh, char *key, char *value)
{
	t_list	*new;

	new = ft_lstnew((void *)new_env(key, value));
	if (new == NULL)
		error_safe_exit("malloc error", 1);
	msh->env = new;
	add_to_garbage_collector((void *)&msh->env, ENV);
}

int	env_iter(t_minishell *msh, char *env, int j, int k)
{
	char	*key;
	char	*value;

	while (env[j] != '=')
		j++;
	key = str_from_range(env, 0, j++);
	if (!key)
		return (0);
	while (env[j + k])
		k++;
	value = str_from_range(env, j, k);
	if (!value)
		return (0);
	if (msh->env == NULL)
		handle_env_null(msh, key, value);
	else
		ft_lstadd_back(&msh->env, ft_lstnew((void *)new_env(key, value)));
	return (1);
}
