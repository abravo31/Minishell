/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:29:47 by motero            #+#    #+#             */
/*   Updated: 2022/11/23 01:32:12 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*new_s;
	size_t		i;
	size_t		j;

	if (!s1 && !s2)
		return (NULL);
	new_s = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!new_s || (s1 == NULL && s2 == NULL))
		return (free(new_s), NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		new_s[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		new_s[i + j] = s2[j];
		j++;
	}
	new_s[i + j] = '\0';
	return (new_s);
}

/*int	main()
{
	char	s1[] = "lorem ipsum";
	char	s2[] = "dolor sit amet";

	char	*strjoin;

	if(!(strjoin = ft_strjoin(s1, s2)))
		printf(" NULL");
	else
		printf("\n %s", strjoin);
}*/
