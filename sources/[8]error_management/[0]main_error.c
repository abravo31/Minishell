/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:02:50 by motero            #+#    #+#             */
/*   Updated: 2023/01/30 18:16:04 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_management.h"

void	error_safe_exit(char *msg)
{
	perror(msg);
	perror(strerror(errno));
	free_garbage_collector();
	exit(EXIT_FAILURE);
}
