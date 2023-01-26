/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]redirection_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:26:31 by motero            #+#    #+#             */
/*   Updated: 2023/01/26 23:39:31 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	redirect_output(t_minishell *msh, t_ast *root)
{
	int		fd;
	t_ast	*right;

	right = root->right;
	fd = open(right->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Error: %s\n", strerror(errno));
		return ;
	}
	ft_lstadd_front(&msh->fd, ft_lstnew(&fd));
}

void	redirect_input(t_minishell *msh, t_ast *root)
{
	int		fd;
	t_ast	*right;

	right = root->right;
	fd = open(right->data, O_RDONLY, 0644);
	if (fd == -1)
	{
		printf("Error: %s\n", strerror(errno));
		return ;
	}
	ft_lstadd_front(&msh->fd, ft_lstnew(&fd));
}

void	redirect_append(t_minishell *msh, t_ast *root)
{
	int		fd;
	t_ast	*right;

	right = root->right;
	fd = open(right->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("Error: %s\n", strerror(errno));
		return ;
	}
	ft_lstadd_front(&msh->fd, ft_lstnew(&fd));
}

void	redirect_heredoc(t_minishell *msh, t_ast *root)
{
	int		fd;
	t_ast	*right;

	right = root->right;
	fd = open(right->data, O_RDONLY, 0644);
	if (fd == -1)
	{
		printf("Error: %s\n", strerror(errno));
		return ;
	}
	ft_lstadd_front(&msh->fd, ft_lstnew(&fd));
}
