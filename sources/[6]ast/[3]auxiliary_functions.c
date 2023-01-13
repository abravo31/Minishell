/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3]auxiliary_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:33:27 by motero            #+#    #+#             */
/*   Updated: 2023/01/14 00:23:39 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

size_t	ft_lstlen(t_list *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

int	is_redirection(t_cmd *cmd)
{
	return (cmd->id == L_REDIR
		|| cmd->id == L_DREDIR
		|| cmd->id == R_REDIR
		|| cmd->id == R_DREDIR);
}
