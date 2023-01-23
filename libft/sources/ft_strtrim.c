/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:58:58 by motero            #+#    #+#             */
/*   Updated: 2022/05/11 19:39:24 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size_s1;

	if (!set || !s1)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1)
		s1++;
	size_s1 = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[size_s1]) && *s1)
		size_s1--;
	return (ft_substr((char *)s1, 0, size_s1 + 1));
}

/*int	main()
{
	char	*str[] = "Lorem ipsum sa maman";
	char	*trim[]= "ipsum";
	char	*new_s;

	new_s = ft_strtrim();
}*/
