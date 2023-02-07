/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [5]builtins_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:06:23 by motero            #+#    #+#             */
/*   Updated: 2023/02/07 00:14:23 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//ast root a simple builtin
void	simple_builtin_traverse(t_minishell *msh, t_ast *root, int *i)
{
	t_ast	*left;

	if (root == NULL)
		return ;
	left = root->left;
	(void)left;
	left->pipe_fd[0] = root->pipe_fd[0];
	left->pipe_fd[1] = root->pipe_fd[1];
	fds_handlings(msh, root, i);
	execute_builtin(msh, root);
	if (*i == 0 || *i == -2)
	{
		dup2(msh->fd_dup[0], STDIN_FILENO);
		dup2(msh->fd_dup[1], STDOUT_FILENO);
		free_garbage_collector(EXCEPT_ENV);
	}
	else
		free_garbage_collector(ALL);
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
	if (*i == -3)
		return ;
	main_execution(msh, right, i);
	if (*i == 0 || *i == -2)
		free_garbage_collector(EXCEPT_ENV);
	else
		free_garbage_collector(ALL);
	(void)i;
}
