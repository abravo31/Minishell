/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo31 <abravo31@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:25:29 by abravo            #+#    #+#             */
/*   Updated: 2023/02/05 20:46:24 by abravo31         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//IMPORTANT check malloc failed
t_cmd	*new_cmd(char *cmd, t_token id, int space)
{
	t_cmd	*elem;

	elem = malloc(sizeof(t_cmd));
	elem->cmd = cmd;
	elem->id = id;
	elem->space = space;
	return (elem);
}

int	is_identical(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] == '\0');
}

char	*ft_strjoin_cmd(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;
	size_t	size;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	size = (ft_strlen(s1) + ft_strlen(s2));
	dest = malloc(sizeof(char) * (size + 1));
	i = -1;
	j = -1;
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[++j])
		dest[i + j] = s2[j];
	dest[i + j] = '\0';
	return (dest);
}

void	get_char(char c, char **cmd)
{
	char	*tmp;

	if (!*cmd)
	{
		*cmd = ft_strdup("?");
		*cmd[0] = c;
		return ;
	}
	tmp = ft_strjoin(*cmd, "?");
	free(*cmd);
	tmp[ft_strlen(tmp) - 1] = c;
	*cmd = tmp;
}

//Function to display syntax error at character where.
char	*syntax_error(char where)
{
	char	*ret;

	if (where == '\n')
	{
		ret = ft_strdup("syntax error near unexpected token \'newline\'");
		if (!ret)
		{
			free_garbage_collector(ALL);
			printf("error while adding a delimitor, \
			still not error or way toe xit this function!\n");
			exit(2);
		}
		add_to_garbage_collector((void *)&ret, INT);
		return (ret);
	}
	ret = ft_strdup("syntax error near unexpected token \'?\'");
	if (!ret)
	{
		free_garbage_collector(ALL);
		printf("error while adding a delimitor, still \
		not error or way toe xit this function!\n");
		exit(2);
	}
	ret[ft_strlen(ret) - 2] = where;
	add_to_garbage_collector((void *)ret, INT);
	return (ret);
}
