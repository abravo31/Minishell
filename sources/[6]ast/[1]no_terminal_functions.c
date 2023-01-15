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
				 ;
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


/*
pipe_sequence - function that creates an AST node for a pipe sequence.
A pipe sequence is a series of one or more complex commands separated by the pipe operator '|'.
This function takes a pointer to a linked list of tokens and an index.
It starts by creating a left AST node with the first complex command.
Then it loops through the linked list while the current token is a pipe operator.
For each iteration, it moves to the next token and creates a right AST node with the next pipe sequence.
If there are no more pipe operators, the right AST node is set to NULL.
Finally, it returns an AST node with the type PIPE_SEQUENCE and left and right children set to the left and right AST nodes.
*/
t_ast	*pipe_sequence(t_list **head, int *i)
{
	t_ast			*left;
	t_ast			*right;

	if (!head || !(*head))
		return (NULL);
	left = complexe_command(head, i);
	right = NULL;
	while ((*head) && ((t_cmd *)(*head)->content)->id == PIPE)
	{
		*head = (*head)->next;
		(*i)++;
		right = pipe_sequence(head, i);
	}
	if (!(*head) && !right)
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
		left = redirection(head, i);
		right = complexe_command(head, i);
	}
	if ((*head) && ((t_cmd *)(*head)->content)->id == UNASSIGNED)
	{
		left = simple_command(head, i);
		right = complexe_command(head, i);
	}
	if (right == NULL)
		return (left);
	if (left == NULL)
		return (right);
    return create_ast_no_terminal(COMPLEXE_COMMAND, left, right);
}

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
