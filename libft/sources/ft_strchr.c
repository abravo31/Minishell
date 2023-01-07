/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:41:30 by motero            #+#    #+#             */
/*   Updated: 2022/05/11 16:40:20 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s_cpy;
	size_t	s_len;
	int		c_256;

	c_256 = c % 256;
	s_cpy = (char *)s;
	s_len = ft_strlen(s);
	if (c_256 == '\0')
		return (s_cpy + s_len);
	else
	{
		s_len = 0;
		while (s_cpy[s_len])
		{
			if (s_cpy[s_len++] == c_256)
				return ((char *)s_cpy + (--s_len));
		}
		return (NULL);
	}
}

/*#include <string.h>

int	main()
{
	const char str[] = "tripouille";
	const char str0[] = "tripouille";
	const char ch = 't';
	char *ret;
	char *ret0;

	ret = ft_strchr(str, ch + 256);
	ret0 = strchr(str0, ch + 256);

	printf("String after |%c| is - |%s|\n", ch, ret);
	printf("String after |%c| is - |%s|\n", ch, ret0);


	return(0);


}*/
