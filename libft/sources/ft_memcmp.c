/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 20:59:09 by motero            #+#    #+#             */
/*   Updated: 2022/05/10 17:21:36 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_cpy;
	unsigned char	*s2_cpy;

	if (n != 0)
	{
		s1_cpy = (unsigned char *) s1;
		s2_cpy = (unsigned char *) s2;
		if (*s1_cpy++ != *s2_cpy++)
			return ((*--s1_cpy) - (*--s2_cpy));
		while (--n)
		{
			if (*s1_cpy++ != *s2_cpy++)
				return ((*--s1_cpy) - (*--s2_cpy));
		}
	}
	return (0);
}

/*#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    int array1 [] = { 54, 85, 20, 63, 21 };
    int array2 [] = { 54, 85, 19, 63, 21 };
    size_t size = sizeof( int ) * 5;

    assert( memcmp( array1, array2, size) == ft_memcmp( array1, array2, size) );
    assert( memcmp( array1, array1, size) == ft_memcmp( array1, array1, size) );
    assert( memcmp( array2, array1, size) == ft_memcmp( array2, array1, size) );

    printf( "Test is ok\n" );

    return 0;
}*/
