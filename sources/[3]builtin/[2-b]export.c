/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2-b]export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo31 <abravo31@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/02/11 15:20:15 by abravo31         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export with no options
int	builtin_export(t_minishell *msh, t_ast *root)
{
	t_list	*env;
	char	**arg;
	int		i;

	g_status = 0;
	if (root->right == NULL)
		return (print_sorted_env(msh), 0);
	env = msh->env;
	arg = root->right->left->arg;
	i = 1;
	while (arg[i])
	{
		if (is_valid_export(arg[i]))
			export_env_value(msh, env, arg[i], 0);
		i++;
	}
	return (1);
}

int	check_if_key(t_env *env, char *str, int i, int j)
{
	int	len;

	while (env && env->key && env->key[i] && str[i] == env->key[i])
		i++;
	if (str[i] && (str[i] == '=' || str[i] == '+') && !env->key[i++])
	{
		if (str[i - 1] == '+')
			return (append_export(env, str, i + 1), 1);
		if (str[i] == 0)
			len = 1;
		else
			len = ft_strlen(str + i) + 1;
		free(env->value);
		env->value = malloc((sizeof (char)) * len);
		if (!env->value)
			error_safe_exit("Malloc failed", 1);
		while (str[i])
			env->value[j++] = str[i++];
		env->value[j] = '\0';
		if (!env->value)
			return (0);
	}
	else
		return (0);
	return (1);
}

char	*fill_new_key(char *str, int end)
{
	char	*key;
	int		j;

	j = 0;
	key = malloc((sizeof (char)) * (end + 1));
	if (!key)
		error_safe_exit("Malloc failed", 1);
	while (str[j] && j < end)
	{
		key[j] = str[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

char	*fill_new_value(char *str, int start, int j, int i)
{
	char	*value;
	int		k;

	if (str[start] == '+')
		start++;
	k = start + 1;
	while (str && str[start])
	{
		start++;
		j++;
	}
	if (!str)
		value = (NULL);
	else
	{
		value = malloc((sizeof (char)) * (j + 1));
		if (!value)
			error_safe_exit("Malloc failed", 1);
	}
	while (str && str[k])
		value[i++] = str[k++];
	value[i] = '\0';
	return (value);
}

void	export_env_value(t_minishell *msh, t_list *env, char *str, int i)
{
	t_env	*env_var;
	t_list	*tmp;
	char	*key;
	char	*value;
	t_list	*new;

	tmp = env;
	while (tmp)
	{
		env_var = tmp->content;
		if (check_if_key(env_var, str, 0, 0) == 1)
			return ;
		tmp = tmp->next;
	}
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	if (!str[i])
		return ;
	key = fill_new_key(str, i);
	value = fill_new_value(str, i, 0, 0);
	new = ft_lstnew((void *)new_env(key, value));
	if (!new)
		error_safe_exit("Malloc failed", 1);
	ft_lstadd_back(&msh->env, new);
}
