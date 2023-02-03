/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]ft_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/01/09 23:11:51 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "structures.h"

int	builtin_export(t_minishell *msh, t_ast *root)
{
	(void)msh;
	(void)root;
	return (printf("Execute export\n"));
}

int	builtin_unset(t_minishell *msh, t_ast *root)
{
	(void)msh;
	(void)root;
	return (printf("Execute unset\n"));
}

int	builtin_env(t_minishell *msh, t_ast *root)
{
	(void)msh;
	(void)root;
	return (printf("Execute env\n"));
}
