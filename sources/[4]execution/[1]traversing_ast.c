/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]traversing_ast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:21:25 by motero            #+#    #+#             */
/*   Updated: 2023/02/01 22:57:02 by motero           ###   ########.fr       */
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
	if (!right)
		*i = -99;
	if (pipe(left->pipe_fd) == -1)
		error_safe_exit("PIPE ERROR\n");
	add_to_garbage_collector((void *)&left->pipe_fd[0], FD);
	add_to_garbage_collector((void *)&left->pipe_fd[1], FD);
	pid = fork();
	if (pid < 0)
		error_safe_exit("FORK ERROR\n");
	if (pid == 0)
	{
		close(left->pipe_fd[0]);
		main_execution(msh, left, i);
		free_garbage_collector();
		exit(EXIT_SUCCESS);
	}
	else
		add_pid_to_list(msh, pid);
	close(left->pipe_fd[1]);
	dup2(left->pipe_fd[0], STDIN_FILENO);
	main_execution(msh, right, i);
	if (!right)
	{
		printf("Last command of a PIPE_SEQUENCE\n");
		close(left->pipe_fd[0]);
		close(left->pipe_fd[1]);
	}
	printf("Start of a PIPE_SEQUENCE\n");
}

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
	//printf("Start of a COMPLEXE_COMMAND\n");
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
	if (msh->fd_out == -1 || msh->fd_in == -1)
		error_safe_exit("FD ERROR\n");
	if (msh->fd_in > 0)
	{
		dup2(msh->fd_in, STDIN_FILENO);
	}
	if (msh->fd_out > 0)
	{
		dup2(msh->fd_out, STDOUT_FILENO);
	}
	else if (*i > 0)
	{
		dup2(root->pipe_fd[1], STDOUT_FILENO);
	}
	if (msh->fd_in > 0 && *i > 0)
	{
		dup2(msh->fd_in, STDIN_FILENO);
		close(msh->fd_in);
	}
	left = root->left;
	if (!left)
		error_safe_exit("AST EXECUTION ERROR, no command\n");
	right = root->right;
	file = ft_check_access(msh, left);
	if (!file)
		file = left->data;
	if (right)
		args = right->left->arg;
	else
		args = get_char_double_ptr(left->data);
	execve(file, args, msh->envp);
	free_double_pointer((void **)args);
	(void)i;
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
	//printf("Start of a ARGUMENT\n");
	main_execution(msh, left, i);
	main_execution(msh, right, i);
	(void)i;
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
	printf("Start of a REDIRECTION\n");
	if (ft_strcmp(">", left->data) == 1)
		redirect_output(msh, root, i);
	else if (ft_strcmp("<", left->data) == 1)
		redirect_input(msh, root, i);
	else if (ft_strcmp(">>", left->data) == 1)
		redirect_append(msh, root, i);
	else if (ft_strcmp("<<", left->data) == 1)
		redirect_heredoc(msh, root, i);
	printf("\n");
	(void)i;
}

//ast root a simple builtin
void	simple_builtin_traverse(t_minishell *msh, t_ast *root, int *i)
{
	t_ast	*left;
	t_ast	*right;

	if (root == NULL)
		return ;
	left = root->left;
	right = root->right;
	main_execution(msh, left, i);
	main_execution(msh, right, i);
	printf("Start of a SIMPLE_BUILTIN\n");
	printf("Command: %s", left->data);
	printf("Args: %s\n\n", right->data);
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
	main_execution(msh, left, i);
	main_execution(msh, right, i);
	printf("Start of a CMPLX_BUILT\n");
	(void)i;
}
