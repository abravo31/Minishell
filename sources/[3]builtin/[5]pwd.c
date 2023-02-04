/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [5]pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/02/04 22:53:26 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(t_minishell *msh, t_ast *root)
{
	char	*path;

	path = getcwd_until_path_fits();
	if (path == NULL)
		return (error_safe_exit("pwd: error: unknown error"), 1);
	add_to_garbage_collector(path, INT);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	(void)msh;
	(void)root;
	return (0);
}
