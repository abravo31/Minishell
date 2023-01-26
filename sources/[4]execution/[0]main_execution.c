/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:52:02 by motero            #+#    #+#             */
/*   Updated: 2023/01/26 21:56:55 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	main_execution(t_minishell *msh, t_ast *root)
{
	if (root == NULL)
		return ;
	if (root->id->op == PIPE_SEQUENCE)
		pipe_sequence_traverse(msh, root);
	else if (root->id->op == COMPLEXE_COMMAND)
		complex_command_traverse(msh, root);
	else if (root->id->op == SIMPLE_COMMAND)
		simple_command_traverse(msh, root);
	else if (root->id->op == ARGUMENT)
		argument_traverse(msh, root);
	else if (root->id->op == REDIRECTION)
		redirection_traverse(msh, root);
	else if (root->id->op == SIMPLE_BUILTIN)
		simple_builtin_traverse(msh, root);
	else if (root->id->op == CMPLX_BUILT)
		complex_builtin_traverse(msh, root);
}

void	execution_terminal(t_minishell *msh, t_ast *root)
{
	(void)msh;
	if (root == NULL)
		return ;
	printf("%s  ", root->data);
}
