
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]ft_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/01/09 23:11:51 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// export with no options
int	builtin_export(t_minishell *msh, t_ast *root)
{
	t_list	*env;
	char	**arg;
	int		i;

	if (root->right == NULL)
		return (print_sorted_env(msh), 0);
	env = msh->env;
	arg = root->right->left->arg;
	i = 1;
	while (arg[i])
	{
		if (is_valid_export(arg[i]))
			export_env_value(msh, env, arg[i]);
		i++;
	}
	return (1);
}

int	check_if_key(t_env *env, char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (env && env->key && env->key[i] && str[i] == env->key[i])
		i++;
	if (str[i] && str[i] == '=' && !env->key[i++])
	{
		free(env->value);
		if (str[i] == 0)
			len = 1;
		else
			len = ft_strlen(str + i) + 1;
		env->value = malloc((sizeof (char)) * len);
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
		return (NULL);
	while (str[j] && j < end)
	{
		key[j] = str[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

//ATTENTION!!! cette fonction ret NULL dans 2 cas !=, on peut avoir un souci
char	*fill_new_value(char *str, int start, int j, int i)
{
	char	*value;
	int		k;

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
			return (NULL);
	}
	while (str && str[k])
	{
		value[i] = str[k];
		i++;
		k++;
	}
	value[i] = '\0';
	return (value);
}

void	export_env_value(t_minishell *msh, t_list *env, char *str)
{
	t_env	*env_var;
	t_list	*tmp;
	char	*key;
	char	*value;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		env_var = tmp->content;
		if (check_if_key(env_var, str) == 1)
			return ;
		tmp = tmp->next;
	}
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return ;
	key = fill_new_key(str, i);
	value = fill_new_value(str, i, 0, 0);
	ft_lstadd_back(&msh->env, ft_lstnew((void *)new_env(key, value)));
}
