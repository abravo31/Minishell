/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:16:18 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/05 20:33:21 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand(char *str, int *index, int *n, t_minishell *msh)
{
	int		i;
	char	c;
	char	*value;

	i = 1;
	if (ft_isdigit(str[0]))
		return ((*index)++, "");
	if (str[0] == '"')
		return ("");
	if ((!ft_isalnum(str[0]) && str[0] != '_') || str[0] == '$')
		return ((*n)++, "$");
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	c = str[i];
	str[i] = '\0';
	value = get_env_value_build(index, msh, str);
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
		return (free(s1), NULL);
	ft_strcpy(temp, s1);
	ft_strcpy(temp + s1len, s2);
	free(s1);
	return (temp);
}

char	*ft_expand(t_minishell *msh, int id, char *str)
{
	char	*new;
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
			new = ft_boost(new, expand(&str[i], &i, &n, msh), \
			ft_strlen(&str[i]));
			if (!new)
				return (NULL);
		}
		if (!str[i])
			break ;
		new[n++] = str[i++];
	}
	return (new);
}

void	expanded_cmd_list(t_minishell *msh)
{
	t_list	*iter;
	t_cmd	*current;

	iter = msh->cmd;
	current = NULL;
	while (iter)
	{
		current = (t_cmd *) iter->content;
		current->cmd = ft_expand(msh, current->id, current->cmd);
		iter = iter->next;
	}
}
