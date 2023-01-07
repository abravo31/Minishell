/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:17:13 by motero            #+#    #+#             */
/*   Updated: 2022/11/23 01:13:33 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*buffer;

	ch = c;
	buffer = NULL;
	while (1)
	{
		if (*s == ch)
			buffer = (char *)s;
		if (*s++ == '\0')
			return (buffer);
	}
	return (buffer);
}
/*int main ()
{
  char str[] = "This is a sample string";
  char *pch;
  printf ("Last occurence of 's' found at %ld \n",pch-str+1);
  return 0;
}*/
