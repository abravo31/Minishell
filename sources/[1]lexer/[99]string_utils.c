/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [99]string_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:25:29 by abravo            #+#    #+#             */
/*   Updated: 2023/02/02 21:17:20 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
