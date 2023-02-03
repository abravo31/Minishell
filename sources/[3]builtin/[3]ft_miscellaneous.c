/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3]ft_miscellaneous.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/01/11 14:27:53 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "structures.h"

int	builtin_echo(t_minishell *msh, t_ast *root)
{
	(void)msh;
	(void)root;
	ft_putstr_fd("Execute echo\n", STDOUT_FILENO);
	return (1);
}

int	builtin_exit(t_minishell *msh, t_ast *root)
{
	(void)msh;
	(void)root;
	return (printf("Execute CD"));
}
