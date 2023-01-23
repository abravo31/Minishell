/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:59:32 by motero            #+#    #+#             */
/*   Updated: 2022/05/10 17:37:21 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	if (*s1 != *s2++)
		return (*(unsigned char *)s1 - *(unsigned char *)--s2);
	if (*s1++ == 0)
		return (0);
	while (--n)
	{
		if (*s1 != *s2++)
			return (*(unsigned char *)s1 - *(unsigned char *)--s2);
		if (*s1++ == 0)
			break ;
	}
	return (0);
}
// C, C++ program to demonstrate
// functionality of strncmp()

/*#include <stdio.h>
#include <string.h>

int main()
{
	// Take any two strings
	char str1[10] = "";
	char str2[10] = "akash";

	// Compare strings using strncmp()
	int result = ft_strncmp(str1, str2, 10);

	if (result == 0) {
		// num is the 3rd parameter of strncmp() function
		printf("str1 is equal to str2 upto num characters\n");
	}
	else if (result > 0)
		printf("str1 is greater than str2\n");
	else
		printf("str2 is greater than str1\n");

	printf("Value returned by strncmp() is: %d", result);

	return 0;
}*/
