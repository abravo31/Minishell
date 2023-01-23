/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:17:51 by motero            #+#    #+#             */
/*   Updated: 2022/11/23 01:23:33 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cal_len(unsigned int start, size_t len, size_t strlen)
{
	if (start > (unsigned int)len)
		return (0);
	else if ((strlen - start) < len)
		return (strlen - start);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (start > len)
	{
		new_s = (char *)malloc(sizeof(char));
		if (!new_s)
			return (NULL);
		return (new_s[0] = 0, new_s);
	}
	len = ft_cal_len(start, len, ft_strlen(s));
	new_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_s || !s)
		return (NULL);
	while (s[start + i] && (start < ft_strlen((char *)s)) && i < len)
	{
		new_s[i] = s[start + i];
		i++;
	}
	return (new_s[i] = '\0', new_s);
}

/*int	main()
{
	char	str[] = "lorem ipsum dolor sit amet";
	char	*strsub;
	
	if (!(strsub = ft_substr(str, 0, 10)))
		printf("NULL");
	else
		printf("\n %s \n", strsub);
	return (0);
}*/
