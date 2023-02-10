/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:16:18 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/10 19:39:07 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lenof(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = (n < 0);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_stoval(t_minishell *msh, int n)
{
	int				i;
	int				len;
	unsigned int	nb;

	nb = -(n < 0) * (n) + (n > 0) * (n);
	i = (n < 0);
	len = lenof(n);
	if (n < 0)
		msh->value[0] = '-';
	msh->value[len] = 0;
	while (--len >= i)
	{
		msh->value[len] = (nb % 10) + '0';
		nb /= 10;
	}
}

char	*ft_get_status(t_minishell *msh, int *n, int *i)
{
	*n += lenof(g_status);
	*i += 1;
	ft_stoval(msh, g_status);
	return (msh->value);
}

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
	if ((!ft_isalnum(str[0]) && str[0] != '_' && str[0] != '?'))
		return ((*n)++, "$");
	while (str[i] && (ft_isalnum(str[i]) || str[0] == '?' || str[i] == '_'))
		i++;
	c = str[i];
	str[i] = '\0';
	if (*str == '?')
		return (str[i] = c, ft_get_status(msh, n, index));
	value = get_env_value(index, msh, str);
	str[i] = c;
	if (!value)
		return ("");
	*n += ft_strlen(value);
	return (value);
}

char	*ft_boost(int id, char *s1, char *s2, int size)
{
	char	*temp;
	size_t	s1len;
	size_t	s2len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	temp = ft_calloc(s1len + s2len + size + 1, 1);
	if (!temp)
		return (free(s1), error_message("Malloc failed : boost", 1), NULL);
	ft_strcpy(temp, s1);
	ft_strcpy(temp + s1len, s2);
	free(s1);
	if (!temp[0] && id == WORD)
		return (free(temp), NULL);
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
	if (!new)
		return (error_safe_exit("Malloc failed", 1), NULL);
	while (str && str[i])
	{
		while (str[i] && str[i] == '$')
		{
			i++;
			new = ft_boost(id, new, \
			expand(&str[i], &i, &n, msh), ft_strlen(&str[i]));
		}
		if (!str[i])
			break ;
		new[n++] = str[i++];
	}
	free(str);
	return (new);
}

void	expanded_cmd_list(t_minishell *msh, t_list *iter)
{
	t_cmd	*current;
	char	**tab_cmd;
	int		i;
	int		space;

	tab_cmd = NULL;
	while (iter)
	{
		current = (t_cmd *) iter->content;
		current->cmd = ft_expand(msh, current->id, current->cmd);
		space = current->space;
		if (ft_nbr_clm(current->cmd) > 1 && current->id == WORD)
		{
			if (!tab_cmd)
				tab_cmd = ft_split_expand(current->cmd);
			i = -1;
			while (tab_cmd && tab_cmd[++i])
				insert_to_list(i, tab_cmd[i], &iter);
			((t_cmd *)(iter->content))->space = space;
		}
		iter = iter->next;
	}
	if (tab_cmd)
		ft_free_tab(tab_cmd);
}

// void	expanded_cmd_list(t_minishell *msh)
// {
// 	t_list	*iter;
// 	t_cmd	*current;
// 	int		i;

// 	iter = msh->cmd;
// 	current = NULL;
// 	i = 0;
// 	while (iter)
// 	{
// 		current = (t_cmd *) iter->content;
// 		current->cmd = ft_expand(msh, current->id, current->cmd);
// 		iter = iter->next;
// 		i++;
// 	}
// }
