/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [99]string_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:25:29 by abravo            #+#    #+#             */
/*   Updated: 2023/01/23 22:42:16 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	if (!s)
// 		return (0);
// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

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

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*dest;
// 	size_t	size;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	size = (ft_strlen(s1) + ft_strlen(s2));
// 	dest = malloc(sizeof(char) * (size + 1));
// 	i = 0;
// 	j = 0;
// 	while (s1[i])
// 	{
// 		dest[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		dest[i + j] = s2[j];
// 		j++;
// 	}
// 	dest[i + j] = '\0';
// 	return (dest);
// }

char	*ft_strdup(const char *s)
{
	char	*s1;
	size_t	size;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	size = ft_strlen(s);
	s1 = malloc(sizeof(char) * size + 1);
	if (!s1)
		return (0);
	while (s[i])
	{
		s1[i] = s[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
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
	tmp[ft_strlen(tmp) - 1] = c;
	*cmd = tmp;
}