/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]traversing_ast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:21:25 by motero            #+#    #+#             */
/*   Updated: 2023/01/31 22:37:49 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//Ast root is apipe sequence
void	pipe_sequence_traverse(t_minishell *msh, t_ast *root)
{
	t_ast	*left;
	t_ast	*right;
	int		left_fd[2];
	int		right_fd[2];
	pid_t	pid;

	if (root == NULL)
		return ;
	left = root->left;
	if (!left)
		error_safe_exit("AST EXECUTION ERROR, Impossible structure\n");
	if (pipe(left_fd) == -1)
		error_safe_exit("PIPE ERROR\n");
	add_to_garbage_collector((void *)&left_fd[0], FD);
	add_to_garbage_collector((void *)&left_fd[1], FD);
	pid = fork();
	if (pid < 0)
		error_safe_exit("FORK ERROR\n");
	if (pid == 0)
	{
		// dup2(left_fd[1], STDOUT_FILENO);
		//dup2(msh->fd_in, STDIN_FILENO);
		// close(left_fd[0]);
		// close(left_fd[1]);
		main_execution(msh, left);
		free_garbage_collector();
		exit(EXIT_SUCCESS);
	}
	else
		add_pid_to_list(msh, pid);
	//dup2(left_fd[0], STDIN_FILENO);
	// close(left_fd[0]);
	// close(left_fd[1]);
	right = root->right;
	main_execution(msh, right);
	(void)(right_fd);
	printf("Start of a PIPE_SEQUENCE\n");
}

//ast root a complex command
void	complex_command_traverse(t_minishell *msh, t_ast *root)
{
	t_ast	*left;
	t_ast	*right;

	if (root == NULL)
		return ;
	left = root->left;
	right = root->right;
	//printf("Start of a COMPLEXE_COMMAND\n");
	main_execution(msh, left);
	main_execution(msh, right);
}

//ast root a simple command
void	simple_command_traverse(t_minishell *msh, t_ast *root)
{
	t_ast	*left;
	t_ast	*right;
	char	*file;
	char	**args;

	if (root == NULL)
		return ;
	if (msh->fd_out < 0 || msh->fd_in < 0)
		error_safe_exit("FD ERROR\n");
	//printf("Start of a SIMPLE_COMMAND\n");
	left = root->left;
	if (!left)
		error_safe_exit("AST EXECUTION ERROR, no command\n");
	right = root->right;
	(void)file;
	(void)args;
	file = ft_check_access(msh, left);
	if (!file)
		file = left->data;
	if (right)
		args = right->left->arg;
	else
		args = get_char_double_ptr(left->data);
	execve(file, args, msh->envp);
	free_double_pointer((void **)args);
}

//ast root an argument
void	argument_traverse(t_minishell *msh, t_ast *root)
{
	t_ast	*left;
	t_ast	*right;

	if (root == NULL)
		return ;
	left = root->left;
	right = root->right;
	//printf("Start of a ARGUMENT\n");
	main_execution(msh, left);
	main_execution(msh, right);
}

//ast root a redirection
void	redirection_traverse(t_minishell *msh, t_ast *root)
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
		redirect_output(msh, root);
	else if (ft_strcmp("<", left->data) == 1)
		redirect_input(msh, root);
	else if (ft_strcmp(">>", left->data) == 1)
		redirect_append(msh, root);
	else if (ft_strcmp("<<", left->data) == 1)
		redirect_heredoc(msh, root);
	printf("\n");
}

//ast root a simple builtin
void	simple_builtin_traverse(t_minishell *msh, t_ast *root)
{
	t_ast	*left;
	t_ast	*right;

	if (root == NULL)
		return ;
	left = root->left;
	right = root->right;
	main_execution(msh, left);
	main_execution(msh, right);
	printf("Start of a SIMPLE_BUILTIN\n");
	printf("Command: %s", left->data);
	printf("Args: %s\n\n", right->data);
}

//ast root a complex builtin
void	complex_builtin_traverse(t_minishell *msh, t_ast *root)
{
	t_ast	*left;
	t_ast	*right;

	if (root == NULL)
		return ;
	left = root->left;
	right = root->right;
	main_execution(msh, left);
	main_execution(msh, right);
	printf("Start of a CMPLX_BUILT\n");
}
