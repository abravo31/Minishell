/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]ft_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/01/09 23:11:12 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "structures.h"

int	builtin_cd(t_minishell *msh, t_ast *root)
{
	(void)msh;
	(void)root;
	return (printf("Execute cd\n"));
}

int	builtin_pwd(t_minishell *msh, t_ast *root)
{
	(void)msh;
	(void)root;
	return (printf("Execute pwd\n"));
}
