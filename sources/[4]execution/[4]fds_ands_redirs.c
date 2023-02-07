/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [4]fds_ands_redirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:05:14 by motero            #+#    #+#             */
/*   Updated: 2023/02/06 20:20:51 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//function that handles the fds, dups and closes
void	fds_handlings(t_minishell *msh, t_ast *root, int *i)
{
	struct stat	buf;

	if (msh->fd_out == -1 || msh->fd_in == -1)
		error_safe_exit("FD ERROR\n");
	if (msh->fd_in > 0)
	{
		dup2(msh->fd_in, STDIN_FILENO);
		close(msh->fd_in);
	}
	if (msh->fd_out > 0)
	{
		dup2(msh->fd_out, STDOUT_FILENO);
		close(msh->fd_out);
	}
	else if (*i > 0)
		dup2(root->pipe_fd[1], STDOUT_FILENO);
	if (fstat(root->pipe_fd[1], &buf) == 0)
		close(root->pipe_fd[1]);
	if (msh->fd_in > 0 && *i > 0)
	{
		dup2(msh->fd_in, STDIN_FILENO);
		close(msh->fd_in);
	}
}

//ast root a redirection
void	redirection_traverse(t_minishell *msh, t_ast *root, int *i)
{
	t_ast	*left;
	t_ast	*right;

	if (root == NULL)
		return ;
	left = root->left;
	right = root->right;
	(void) right;
	if (ft_strcmp(">", left->data) == 1)
		redirect_output(msh, root, i);
	else if (ft_strcmp("<", left->data) == 1)
		redirect_input(msh, root, i);
	else if (ft_strcmp(">>", left->data) == 1)
		redirect_append(msh, root, i);
	else if (ft_strcmp("<<", left->data) == 1)
		redirect_heredoc(msh, root, i);
	(void)i;
}
