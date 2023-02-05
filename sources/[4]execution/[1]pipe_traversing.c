/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]pipe_traversing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:12:02 by motero            #+#    #+#             */
/*   Updated: 2023/02/02 21:13:30 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//Ast root is apipe sequence
void	pipe_sequence_traverse(t_minishell *msh, t_ast *root, int *i)
{
	t_ast	*left;
	t_ast	*right;
	pid_t	pid;

	*i = *i + 1;
	if (root == NULL)
		return ;
	left = root->left;
	right = root->right;
	if (!left)
		error_safe_exit("AST EXECUTION ERROR, Impossible structure\n");
	(void)right;
	if (!right)
		*i = -1;
	if (pipe(left->pipe_fd) == -1)
		error_safe_exit("PIPE ERROR\n");
	add_to_garbage_collector((void *)&left->pipe_fd[0], FD);
	add_to_garbage_collector((void *)&left->pipe_fd[1], FD);
	pid = fork();
	if (pid < 0)
		error_safe_exit("FORK ERROR\n");
	if (pid == 0)
		child_sequence_traverse(msh, root, i);
	parent_seq_traverse(msh, root, i, pid);
}

void	child_sequence_traverse(t_minishell *msh, t_ast *root, int *i)
{
	t_ast	*left;

	left = root->left;
	close(left->pipe_fd[0]);
	close(msh->fd_dup[0]);
	close(msh->fd_dup[1]);
	main_execution(msh, left, i);
	free_garbage_collector(ALL);
	exit(EXIT_SUCCESS);
}

void	parent_seq_traverse(t_minishell *msh, t_ast *root, int *i, pid_t pid)
{
	t_ast	*left;
	t_ast	*right;

	left = root->left;
	right = root->right;
	add_pid_to_list(msh, pid);
	sig_ignore_all();
	close(left->pipe_fd[1]);
	dup2(left->pipe_fd[0], STDIN_FILENO);
	close(left->pipe_fd[0]);
	main_execution(msh, right, i);
	if (!right)
	{
		close(left->pipe_fd[0]);
		close(left->pipe_fd[1]);
	}
}
