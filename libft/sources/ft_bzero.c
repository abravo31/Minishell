/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:17:34 by motero            #+#    #+#             */
/*   Updated: 2022/05/09 13:40:00 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

/*int	main()*/
/*{*/
	/*int n = 10;*/
	/*int arr[10];*/

	/*// Fill whole array with 0.*/
	/*bzero(arr, n);*/
	/*[>printf("\nArray after ()\n");<]*/
	/*[>printArray(arr, n);<]*/

	/*int arr1[10];*/

	/*// Fill whole array with 0.*/
	/*ft_bzero(arr1, n);*/
	/*)*/
	/*printf("\nArray after ft_memset\n");*/
	/*[>printArray(arr1, n);<]*/
	/*return 0;*/

	/*return 0;*/
/*}*/
