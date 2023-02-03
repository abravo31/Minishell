/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:29:23 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/03 21:45:35 by abravo           ###   ########.fr       */
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

t_env	*new_env(char *key, char *value)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env)); //IMPORTANT check malloc failed
	elem->key = key;
	elem->value = value;
	return (elem);
}

char	*str_from_range(char *env, int start, int size)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (i < size)
	{
		str[i] = env[start + i];
		i++;
	}
    str[i] = '\0';
	return (str);
}

int	get_env(char **env, t_minishell *msh)
{
	int	i;
	int	j;
	int k;
	char	*key;
	char	*value;

	i = 0;
	if (!env)
		ft_lstadd_back(&msh->env, ft_lstnew((void *)new_env(NULL, NULL)));
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
            j++;
		if (!(key = str_from_range(env[i], 0, j)))
			return (-1);
		k = 0;
        j++;
		while (env[i][j + k])
		    k++;
        if (!(value = str_from_range(env[i], j, k)))
			return (-1);
		ft_lstadd_back(&msh->env, ft_lstnew((void *)new_env(key, value)));
        i++;
	}
    //__debug_env(msh);
    return(0);
}

char	*get_value_from_key(t_minishell *msh, char *key)
{
	t_list	**temp;
	t_env	*temp2;

	temp = &msh->env;
	temp2 = NULL;
	while (*temp)
	{	
		temp2 = (t_env *) (*temp)->content;
		if (ft_strcmp(key, temp2->key))
			return (temp2->value);
		*temp = (*temp)->next;
	}
	return (NULL);
}

char	*expand(char *str, int *index, int *n, t_minishell *msh)
{
	int i = 1;

	if (ft_isdigit(str[0]))
		return((*index)++, "");
	if (str[0] == '"') // si le premier charactere du prochain element est un guillement on renvoit rien
		return ("");
	if ((!ft_isalnum(str[0]) && str[0] != '_') || str[0] == '$')
		return ((*n)++, "$");
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	char c = str[i];
	str[i] = '\0';
	int len = ft_strlen(str);
	*index += len;
	t_list *head = msh->env;
	char *value = get_value_from_key(msh, str);
	msh->env = head;
	str[i] = c;
	if (!value)
		return ("");
	*n += ft_strlen(value);
	return (value);
}

char	*ft_boost(char *s1, char *s2, int size)
{
	char	*temp;
	size_t	s1len;
	size_t	s2len;

	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	temp = ft_calloc(s1len + s2len + size + 1, 1);
	if (!temp)
	{
		free(s1);
		return (NULL);	
	}
	ft_strcpy(temp, s1);
	ft_strcpy(temp + s1len, s2);
	free(s1);
	return (temp);
}

char	*ft_expand(t_minishell *msh, int id, char *str)
{
	char *new;
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (id == 7)
		return (str);
	new = ft_calloc(ft_strlen(str) + 1, 1);
	while (str && str[i])
	{
		while (str[i] && str[i] == '$')
		{
			i++;
			new = ft_boost(new, expand(&str[i], &i, &n, msh), ft_strlen(&str[i]));
			if (!new)
				return (NULL);
		}
		if (!str[i])
			break;
		new[n++] = str[i++];
	}
	return (new);
}

void	__debug_parsing_expand(t_minishell *msh)
{
	t_list	*iter;
	t_cmd	*current;

	iter = msh->cmd;
	current = NULL;
	while (iter)
	{
		current = (t_cmd *) iter->content;
		printf("(%d){%d}[%s]\n", current->space, current->id, ft_expand(msh, current->id, current->cmd));//proteger expand
		iter = iter->next;
	}
}
/*

str = ls $HOME
new = ls 
*/