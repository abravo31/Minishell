/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]redirection_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:26:31 by motero            #+#    #+#             */
/*   Updated: 2023/02/06 23:54:16 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	redirect_output(t_minishell *msh, t_ast *root, int *i)
{
	int		fd;
	t_ast	*right;

	if (*i == 0)
		*i = -2;
	right = root->right;
	if (msh->fd_out == -1)
		error_safe_exit("FD OUT ERROR\n");
	if (msh->fd_out > 2)
		close(msh->fd_out);
	fd = open(right->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 && *i >= -1)
		error_safe_exit(right->data);
	if (fd == -1 && *i == -2)
	{
		*i = -3;
		return (error_message(right->data, errno));
	}
	msh->fd_out = fd;
	add_to_garbage_collector(&fd, FD);
	(void)i;
}

void	redirect_input(t_minishell *msh, t_ast *root, int *i)
{
	int		fd;
	t_ast	*right;

	if (*i == 0)
		*i = -2;
	right = root->right;
	if (msh->fd_in == -1)
		error_safe_exit("FD IN ERROR\n");
	if (msh->fd_in > 2)
		close(msh->fd_out);
	fd = open(right->data, O_RDONLY, 0644);
	if (fd == -1 && *i >= -1)
		error_safe_exit(right->data);
	if (fd == -1 && *i == -2)
	{
		*i = -3;
		return (error_message(right->data, errno));
	}
	msh->fd_in = fd;
	add_to_garbage_collector((void *)&fd, FD);
	(void)i;
}

void	redirect_append(t_minishell *msh, t_ast *root, int *i)
{
	int		fd;
	t_ast	*right;

	if (*i == 0)
		*i = -2;
	right = root->right;
	if (msh->fd_out == -1)
		error_safe_exit("FD APP ERROR\n");
	if (msh->fd_out > 1)
		close(msh->fd_out);
	fd = open(right->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1 && *i >= -1)
		error_safe_exit(right->data);
	if (fd == -1 && *i == -2)
	{
		*i = -3;
		return (error_message(right->data, errno));
	}
	msh->fd_out = fd;
	add_to_garbage_collector((void *)&fd, FD);
	(void)i;
}

void	redirect_heredoc(t_minishell *msh, t_ast *root, int *i)
{
	int		fd;
	t_ast	*right;

	if (*i == 0)
		*i = -2;
	right = root->right;
	if (msh->fd_in == -1)
		error_safe_exit("FD HD ERROR\n");
	if (msh->fd_in > 1)
		close(msh->fd_out);
	fd = open(right->data, O_RDONLY, 0644);
	unlink(right->data);
	if (fd == -1 && *i >= -1)
		error_safe_exit(right->data);
	if (fd == -1 && *i == -2)
	{
		*i = -3;
		return (error_message(right->data, errno));
	}
	msh->fd_in = fd;
	add_to_garbage_collector((void *)&fd, FD);
	(void)i;
}
