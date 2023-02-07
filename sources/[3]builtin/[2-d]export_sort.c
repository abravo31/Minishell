/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2-d]export_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo31 <abravo31@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:08:10 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/07 16:09:29 by abravo31         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp_env(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	sort_env(char **tab, int env_len)
{
	int		sorted;
	int		i;
	char	*tmp;

	sorted = 0;
	while (tab && sorted == 0)
	{
		sorted = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp_env(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
		env_len--;
	}
}

size_t	size_env(t_list *env_lst)
{
	size_t	lst_len;
	t_env	*env_var;

	lst_len = 0;
	while (env_lst && env_lst->next != NULL)
	{
		env_var = env_lst->content;
		if (env_var->key)
		{
			lst_len += ft_strlen(env_var->key);
			lst_len++;
		}
		if (env_var->value != NULL)
		{
			lst_len += ft_strlen(env_var->value);
			lst_len++;
		}
		env_lst = env_lst->next;
	}
	return (lst_len);
}

char	*env_to_str(t_list *env_lst, char *env, t_env *env_var)
{
	int		i;
	int		j;

	i = 0;
	while (env_lst && env_lst->next != NULL)
	{
		env_var = env_lst->content;
		if (env_var->key)
		{
			j = 0;
			while (env_var->key[j])
				env[i++] = env_var->key[j++];
			env[i++] = '=';
			j = 0;
			while (env_var->value[j])
				env[i++] = env_var->value[j++];
		}
		if (env_lst->next->next != NULL)
			env[i++] = '\n';
		env_lst = env_lst->next;
	}
	env[i] = '\0';
	return (env);
}

void	print_sorted_env(t_list *env)
{
	int		i;
	char	**tab;
	char	*str;
	char	*env_tab;

	if (!(env_tab = malloc(sizeof(char) * size_env(env) + 1)))
		return ;
	str = env_to_str(env, env_tab, NULL);
	tab = ft_split(str, '\n');
	free(str);
	sort_env(tab, str_env_len(tab));
	i = 0;
	while (tab[i])
	{
		ft_putstr("declare -x ");
		ft_putstr(tab[i]);
		printf("\n");
		i++;
	}
	ft_free_tab(tab);
}
