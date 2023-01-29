/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]traversing_ast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:21:25 by motero            #+#    #+#             */
/*   Updated: 2023/01/26 22:28:01 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//Ast root is apipe sequence
void	pipe_sequence_traverse(t_minishell *msh, t_ast *root)
{
	t_ast	*left;
	t_ast	*right;

	if (root == NULL)
		return ;
	left = root->left;
	right = root->right;
	main_execution(msh, left);
	main_execution(msh, right);
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
	main_execution(msh, left);
	main_execution(msh, right);
	printf("Start of a COMPLEXE_COMMAND\n");
}

//ast root a simple command
void	simple_command_traverse(t_minishell *msh, t_ast *root)
{
	t_ast	*left;
	t_ast	*right;

	if (root == NULL)
		return ;
	left = root->left;
	right = root->right;
	main_execution(msh, left);
	main_execution(msh, right);
	printf("Start of a SIMPLE_COMMAND\n");
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
	main_execution(msh, left);
	main_execution(msh, right);
	printf("Start of a ARGUMENT\n");
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
