/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3]expand_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo31 <abravo31@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:55:51 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/10 04:00:31 by abravo31         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_nbr_clm(char const *s)
{
	size_t	nbr_words;

	nbr_words = 0;
	while (s && *s)
	{
		if (is_space(*s))
			s++;
		else
		{
			while (*s && !is_space(*s))
				s++;
			nbr_words++;
		}
	}
	return (nbr_words);
}

size_t	ft_len(char const *s)
{
	size_t	len;

	len = 0;
	while (s && *s && !is_space(*s++))
		len++;
	return (len);
}

static void	ft_free_split(char **split, int i)
{
	while (i--)
		free(split[i]);
	free(split);
}

char	**ft_split_expand(char const *s)
{
	char			**split_expand;
	const size_t	nbr_words = ft_nbr_clm(s);
	size_t			len;
	size_t			i;

	split_expand = (char **)malloc(sizeof(char *) * (nbr_words + 1));
	if (!split_expand)
		error_safe_exit("Malloc failed", 1);
	i = 0;
	while (*s && i < nbr_words)
	{
		while (is_space(*s))
			s++;
		len = ft_len(s);
		split_expand[i] = ft_substr(s, 0, len);
		if (!split_expand[i++])
		{
			ft_free_split(split_expand, --i);
			return (NULL);
		}
		s += len;
	}
	split_expand[i] = 0;
	return (split_expand);
}

void	insert_to_list(int i, char *insert, t_list **iter)
{
	t_cmd	*cur;
	t_cmd	*cmd_new;
	t_list	*new;

	cur = (t_cmd *)((*iter)->content);
	cmd_new = NULL;
	if (i == 0)
	{
		free(cur->cmd);
		cur->cmd = ft_strdup(insert);
		cur->space = 1;
		return ;
	}
	cmd_new = new_cmd(ft_strdup(insert), WORD, 1);
	new = ft_lstnew(cmd_new);
	if (*iter == NULL)
	{
		*iter = new;
		return ;
	}
	new->next = (*iter)->next;
	(*iter)->next = new;
	*iter = (*iter)->next;
}
