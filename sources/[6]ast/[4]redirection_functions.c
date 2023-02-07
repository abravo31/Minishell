/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [4]redirection_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:56:22 by motero            #+#    #+#             */
/*   Updated: 2023/02/05 23:48:58 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
This function initializes an array of function pointers with the address of the 
corresponding redirection functions, which are redirection_right, 
redirection_double_right, redirection_left, and redirection_double_left.
The array is indexed by the id of the redirection operator, allowing for easy
lookup and execution of the correct redirection function.
*/
void	init_redirection_function(t_ast *(*redirection_function[4])
(t_list **, int *))
{
	redirection_function[0] = &redirection_right;
	redirection_function[1] = &redirection_double_right;
	redirection_function[2] = &redirection_left;
	redirection_function[3] = &redirection_double_left;
}

/*
Creates a redirection AST node with a cmd_redir node as the left 
child and a cmd_name node as the right child.
*/
t_ast	*redirection_left(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	left = NULL;
	right = NULL;
	left = cmd_redir(head, i);
	if (left == NULL)
		return (NULL);
	right = cmd_filename(head, i);
	if (right == NULL)
		return (NULL);
	right->id->token = FILENAME;
	return (create_ast_no_terminal(REDIRECTION, left, right));
}

/*
Creates a redirection AST node with a cmd_redir node as 
the left child and a cmd_name node as the right child.
*/
t_ast	*redirection_right(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	left = NULL;
	right = NULL;
	left = cmd_redir(head, i);
	if (left == NULL)
		return (NULL);
	right = cmd_filename(head, i);
	if (right == NULL)
		return (NULL);
	right->id->token = FILENAME;
	return (create_ast_no_terminal(REDIRECTION, left, right));
}

/*
Creates a redirection AST node with a cmd_redir node as the 
left child and a cmd_name node as the right child.
*/
t_ast	*redirection_double_left(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	left = NULL;
	right = NULL;
	left = cmd_redir(head, i);
	if (left == NULL)
		return (NULL);
	here_doc((t_cmd *)(*head)->content, i);
	right = cmd_filename(head, i);
	if (right == NULL)
		return (NULL);
	right->id->token = FILENAME;
	return (create_ast_no_terminal(REDIRECTION, left, right));
}

/*
Creates a redirection AST node with a cmd_redir node as 
the left child and a cmd_name node as the right child.
*/
t_ast	*redirection_double_right(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	left = NULL;
	right = NULL;
	left = cmd_redir(head, i);
	if (left == NULL)
		return (NULL);
	right = cmd_filename(head, i);
	if (right == NULL)
		return (NULL);
	right->id->token = FILENAME;
	return (create_ast_no_terminal(REDIRECTION, left, right));
}
