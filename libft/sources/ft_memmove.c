/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:38:58 by motero            #+#    #+#             */
/*   Updated: 2022/05/16 18:43:21 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

	/* By compaing the src and the dst adresses, we should be able to find if 
	 *
	 * they overlap*/
	/* if the beginning of the dest overlaps, copy fro; end to begining*/
	/*if the end of dest overlaps copy from beginning to end*/
	/*if the beginning of dest overlaps or if theyd o not overlaps, cpy ro; beg
	 * to end*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*cdest;
	const char		*csrc;

	if (!dest && !src)
		n = 0;
	if (dest < src)
	{
		csrc = (const char *) src;
		cdest = (char *) dest;
		while (n--)
			*cdest++ = *csrc++;
	}
	else
	{
		csrc = (const char *) src + (n - 1);
		cdest = (char *) dest + (n - 1);
		while (n--)
			*cdest-- = *csrc--;
	}
	return (dest);
}
/*#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int		main(int argc, const char *argv[])
{
	char	src[] = "lorem ipsum dolor sit amet";
	char	*dest;
	int		arg;

	dest = src + 1;
	alarm(5);
	if (argc == 1)
		return (0);
	else if ((arg = atoi(argv[1])) == 1)
	{
		if (dest != memmove(dest, "consectetur", 5))
			write(1, "dest's adress was not returned\n", 31);
		write(1, dest, 22);
	}
	else if (arg == 2)
	{
		if (dest != ft_memmove(dest, "con\0sec\0\0te\0tur", 10))
			write(1, "dest's adress was not returned\n", 31);
		write(1, dest, 22);
	}
	else if (arg == 3)
	{
		if (dest != ft_memmove(dest, src, 8))
			write(1, "dest's adress was not returned\n", 31);
		write(1, dest, 22);
	}
	else if (arg == 4)
	{
		if (src != ft_memmove(src, dest, 8))
			write(1, "dest's adress was not returned\n", 31);
		write(1, dest, 22);
	}
	else if (arg == 5)
	{
		if (src != ft_memmove(src, dest, 0))
			write(1, "dest's adress was not returned\n", 31);
		write(1, dest, 22);
	}
	return (0);
}*/
