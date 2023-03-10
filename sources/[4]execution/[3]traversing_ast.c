/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3]traversing_ast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:21:25 by motero            #+#    #+#             */
/*   Updated: 2023/02/11 17:06:19 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//ast root a complex command
void	complex_command_traverse(t_minishell *msh, t_ast *root, int *i)
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
	main_execution(msh, right, i);
	(void)i;
}

//ast root a simple command
void	simple_command_traverse(t_minishell *msh, t_ast *root, int *i)
{
	t_ast	*left;
	t_ast	*right;
	char	*file;
	char	**args;

	if (root == NULL)
		return ;
	fds_handlings(msh, root, i);
	left = root->left;
	if (!left)
		error_safe_exit("AST EXECUTION ERROR, no command\n", 1);
	right = root->right;
	file = ft_check_access(msh, left);
	if (!file)
		file = left->data;
	if (right)
		args = right->left->arg;
	else
		args = get_char_double_ptr(left->data);
	if (execve(file, args, msh->envp) == -1)
		error_safe_exit(file, 127);
	if (!right)
		free_double_pointer((void **)args);
	exit(127);
}

//ast root an argument
void	argument_traverse(t_minishell *msh, t_ast *root, int *i)
{
	t_ast	*left;
	t_ast	*right;

	if (root == NULL)
		return ;
	left = root->left;
	right = root->right;
	main_execution(msh, left, i);
	main_execution(msh, right, i);
	(void)i;
}
