/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]redirection_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:26:31 by motero            #+#    #+#             */
/*   Updated: 2023/02/02 18:26:07 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	redirect_output(t_minishell *msh, t_ast *root, int *i)
{
	int		fd;
	t_ast	*right;

	right = root->right;
	if (msh->fd_out == -1)
		error_safe_exit("FD ERROR\n");
	if (msh->fd_out > 2)
		close(msh->fd_out);
	fd = open(right->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		error_safe_exit(strerror(errno));
		exit(EXIT_FAILURE);
	}
	msh->fd_out = fd;
	add_to_garbage_collector(&fd, FD);
	(void)i;
}

void	redirect_input(t_minishell *msh, t_ast *root, int *i)
{
	int		fd;
	t_ast	*right;

	right = root->right;
	if (msh->fd_in == -1)
		error_safe_exit("FD ERROR\n");
	if (msh->fd_in > 1)
		close(msh->fd_out);
	fd = open(right->data, O_RDONLY, 0644);
	if (fd == -1)
	{
		error_safe_exit(strerror(errno));
		exit(EXIT_FAILURE);
	}
	msh->fd_in = fd;
	add_to_garbage_collector((void *)&fd, FD);
	(void)i;
}

void	redirect_append(t_minishell *msh, t_ast *root, int *i)
{
	int		fd;
	t_ast	*right;

	right = root->right;
	if (msh->fd_out == -1)
		error_safe_exit("FD ERROR\n");
	if (msh->fd_out > 1)
		close(msh->fd_out);
	fd = open(right->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		error_safe_exit(strerror(errno));
		exit(EXIT_FAILURE);
	}
	msh->fd_out = fd;
	add_to_garbage_collector((void *)&fd, FD);
	(void)i;
}

void	redirect_heredoc(t_minishell *msh, t_ast *root, int *i)
{
	int		fd;
	t_ast	*right;

	right = root->right;
	if (msh->fd_in == -1)
		error_safe_exit("FD ERROR\n");
	if (msh->fd_in > 1)
		close(msh->fd_out);
	fd = open(right->data, O_RDONLY, 0644);
	if (fd == -1)
	{
		error_safe_exit(strerror(errno));
		exit(EXIT_FAILURE);
	}
	msh->fd_in = fd;
	add_to_garbage_collector((void *)&fd, FD);
	(void)i;
}
