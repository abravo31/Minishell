/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:26:52 by motero            #+#    #+#             */
/*   Updated: 2022/09/23 12:02:44 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_len > size)
		dst_len = size;
	if (dst_len == size)
		return (size + src_len);
	if (src_len < (size - dst_len))
		ft_memcpy (dst + dst_len, src, src_len + 1);
	else
	{
		ft_memcpy(dst + dst_len, src, size - dst_len - 1);
		dst[size - 1] = '\0';
	}
	return (src_len + dst_len);
}

/*#include <bsd/string.h>

int	main ()
{
	char *dest;

	if (dest = (char *)malloc(sizeof(*dest) * 15))
		return (0);
	memset(dest, 0, 15);
	memset(dest, 'r', 6);

	char *dest1;

	if (dest1 = (char *)malloc(sizeof(*dest1) * 15))
		return (0);
	memset(dest1, 0, 15);
	memset(dest1, 'r', 6);
	
	dest[0] = '\0';
	dest[11] = 'a';
	printf("base strl %s \n", strlcat(dest, "lorem ipsum", 15));
	printf("base strl %s \n, ft_strlcat(dest, "lorem ipsum", 15));

}*/
