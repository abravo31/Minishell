/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]no_terminal_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:13:22 by motero            #+#    #+#             */
/*   Updated: 2023/01/14 21:59:39 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
the following are the no-terminalf functions of are grammar table
pipe_sequence 	:complexe_command
				| complexe_command '|' pipe_sequence
				;
complexe_command : complexe_command redirection
				 | simple_command 
				 | simple_command redirection
simple_command	: cmd_name
				| cmd_name argument
				;
argument		: cmd_word
				| cmd_word cmd_word
                ;
redirection 	: '<' cmd_word
				|  cmd_word '>' 
				| '<<' cmd_word
				|  cmd_word '>>' 
				;                 
*/

t_ast	*pipe_sequence(t_list **head, int *i)
{
	t_ast			*left;
	t_ast			*right;
	t_cmd			*cmd;

	if ((*head) == NULL)
		return (NULL);
	left = complexe_command(head, i);
	right = NULL;
	(void)cmd;
	while ((*head) && ((t_cmd *)(*head)->content)->id == PIPE)
	{
		cmd = (t_cmd *)(*head)->content;
		*head = (*head)->next;
		(*i)++;
		right = pipe_sequence(head, i);
	}
	if ((*head) == NULL && right == NULL)
		return (left);
	return (create_ast_no_terminal(PIPE_SEQUENCE, left, right));
}

/*complexe_comand function following this new rule
complexe_command : complexe_command redirection
				 | simple_command 
				 | simple_command redirection
				 */

t_ast	*complexe_command(t_list **head, int *i)
{
    t_ast	*left;
	t_ast	*right;

	if ((*head) == NULL)
		return (NULL);
	left = NULL;
	right = NULL;
	if ((*head) && is_redirection((t_cmd *)(*head)->content))
	{
		right = redirection(head, i);
		left = complexe_command(head, i);
	}
	if ((*head) && ((t_cmd *)(*head)->content)->id == UNASSIGNED)
		left = simple_command(head, i);
	if (right == NULL)
		return (left);
    return create_ast_no_terminal(COMPLEXE_COMMAND, left, right);
}

// t_ast	*complexe_command(t_list **head, int *i)
// {
// 	t_ast			*left;
// 	t_ast			*right;

// 	(*i)++;
// 	if ((*head) == NULL)
// 		return (NULL);
// 	left = NULL;
// 	right = NULL;
// 	if (is_redirection((t_cmd *)(*head)->content))
// 	{
// 		left = redirection(head, i);
// 		if ((*head) && ((t_cmd *)(*head)->content)->id == UNASSIGNED)
// 			right = complexe_command(head, i);
// 		else if ((*head) && is_redirection((t_cmd *)(*head)->content))
// 			right = redirection(head, i);
// 	}
// 	else
// 	{
// 		left = simple_command(head, i);
// 		if ((*head) && is_redirection((t_cmd *)(*head)->content))
// 			right = redirection(head, i);
// 	}
// 	if (right == NULL)
// 		return (left);
// 	return (create_ast_no_terminal(COMPLEXE_COMMAND, left, right));
// }

t_ast	*simple_command(t_list **head, int *i)
{
	t_ast			*left;
	t_ast			*right;
	t_cmd			*cmd;

	(void)cmd;
	if ((*head) == NULL)
		return (NULL);
	cmd = (t_cmd *)(*head)->content;
	left = NULL;
	right = NULL;
	if (((t_cmd *)(*head)->content)->id == UNASSIGNED)
	{
		left = cmd_name(head, i);
		if ((*head) && ((t_cmd *)(*head)->content)->id == UNASSIGNED)
			right = argument(head, i);
	}
	return (create_ast_no_terminal(SIMPLE_COMMAND, left, right));
}

t_ast	*argument(t_list **head, int *i)
{
	t_ast			*left;
	t_ast			*right;
	t_cmd			*cmd;

	if ((*head) == NULL)
		return (NULL);
	cmd = (t_cmd *)(*head)->content;
	left = NULL;
	if (cmd->id == UNASSIGNED)
		left = cmd_word(head, i);
	right = NULL;
	return (create_ast_no_terminal(ARGUMENT, left, right));
}
