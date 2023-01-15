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

static void	init_redirection_function(t_ast *(*redirection_function[4])
(t_list **, int *))
{
	redirection_function[0] = &redirection_right;
	redirection_function[1] = &redirection_double_right;
	redirection_function[2] = &redirection_left;
	redirection_function[3] = &redirection_double_left;
}

t_ast	*redirection(t_list **head, int *i)
{
	int			index;
	t_ast		*(*redirection_function[4])(t_list **, int *i);


	init_redirection_function(redirection_function);
	index = 1;
	while (index <= L_DREDIR)
	{
		if (index == (int)((t_cmd *)(*head)->content)->id)
			return (redirection_function[index - 1](head, i));
		index++;
	}
	return (NULL);
}

t_ast	*redirection_left(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	right = cmd_name(head, i);
	left = cmd_redir(head, i);
	return (create_ast_no_terminal(REDIRECTION, left, right));
}

t_ast	*redirection_right(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	ft_printf("redirection_right\n");
	left = cmd_redir(head, i);
	right = cmd_name(head, i);
	return (create_ast_no_terminal(REDIRECTION, left, right));
}

t_ast	*redirection_double_left(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	left = cmd_name(head, i);
	right = cmd_redir(head, i);
	return (create_ast_no_terminal(REDIRECTION, left, right));
}

t_ast	*redirection_double_right(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	right = cmd_redir(head, i);
	left = cmd_name(head, i);
	return (create_ast_no_terminal(REDIRECTION, left, right));
}
