/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:41:30 by motero            #+#    #+#             */
/*   Updated: 2022/11/23 01:29:08 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strconcat(char *dest, char *src)
{
	char	*tmp;

	if (!dest)
		return (NULL);
	if (!src)
		return (dest);
	tmp = ft_strjoin(dest, src);
	free (dest);
	return (tmp);
}
