/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:25:29 by abravo            #+#    #+#             */
/*   Updated: 2023/02/08 19:45:27 by motero           ###   ########.fr       */
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
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	else if ((s1 && !s1[0]) && (s2 && !s2[0]))
		str = ft_strdup("");
	else if (!s1 || !s1[0])
		str = ft_strdup(s2);
	else if (!s2 || !s2[0])
		str = ft_strdup(s1);
	else if (s1 && s2)
		str = ft_strjoin(s1, s2);
	else
		str = ft_strdup("");
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (str);
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
		add_to_garbage_collector((void *)ret, INT);
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
	add_to_garbage_collector((void *)ret, INT);
	ret[ft_strlen(ret) - 2] = where;
	return (ret);
}
