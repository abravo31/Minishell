/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [4]redirection_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:56:22 by motero            #+#    #+#             */
/*   Updated: 2023/01/14 22:24:15 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	init_redirection_function(t_ast *(*redirection_function[4])
(t_list **, int *))
{
	redirection_function[0] = &redirection_right;
	redirection_function[1] = &redirection_double_right;
	redirection_function[2] = &redirection_left;
	redirection_function[3] = &redirection_double_left;
}

t_ast	*redirection_left(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	left = cmd_redir(head, i);
	right = cmd_name(head, i);
	return (create_ast_no_terminal(REDIRECTION, left, right));
}

t_ast	*redirection_right(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	left = cmd_redir(head, i);
	right = cmd_name(head, i);
	return (create_ast_no_terminal(REDIRECTION, left, right));
}

t_ast	*redirection_double_left(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	left = cmd_redir(head, i);
	right = cmd_name(head, i);
	return (create_ast_no_terminal(REDIRECTION, left, right));
}

t_ast	*redirection_double_right(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	left = cmd_redir(head, i);
	right = cmd_name(head, i);
	return (create_ast_no_terminal(REDIRECTION, left, right));
}