/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [5]builtins_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:06:23 by motero            #+#    #+#             */
/*   Updated: 2023/02/02 22:06:46 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//ast root a simple builtin
void	simple_builtin_traverse(t_minishell *msh, t_ast *root, int *i)
{
	t_ast	*left;
	t_ast	*right;

	if (root == NULL)
		return ;
	left = root->left;
	right = root->right;
	(void)left;
	(void)right;
	execute_builtin(msh, root);
	(void)i;
}

//ast root a complex builtin
void	complex_builtin_traverse(t_minishell *msh, t_ast *root, int *i)
{
	t_ast	*left;
	t_ast	*right;

	if (root == NULL)
		return ;
	left = root->left;
	right = root->right;
	left->pipe_fd[0] = root->pipe_fd[0];
	left->pipe_fd[1] = root->pipe_fd[1];
	right->pipe_fd[0] = root->pipe_fd[0];
	right->pipe_fd[1] = root->pipe_fd[1];
	main_execution(msh, left, i);
	simple_builtin_traverse(msh, right, i);
	(void)i;
}
