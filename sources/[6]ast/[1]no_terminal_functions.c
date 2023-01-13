/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]no_terminal_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:13:22 by motero            #+#    #+#             */
/*   Updated: 2023/01/14 00:24:14 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
the following are the no-terminalf functions of are grammar table
pipe_sequence    : complexe_command
				 | complexe_command '|' complexe_command
                 | complexe_command '|' pipe_sequence
                 ;
complexe_command : simple_command 
				 | simple_command redirection
				 | redirection	simple_command
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

t_ast	*pipe_sequence(t_list *head, int *i)
{
	t_ast			*left;
	t_ast			*right;
	t_cmd			*cmd;
	int const		list_len = (int)ft_lstlen(head);

	if (head == NULL)
		return (NULL);
	left = complexe_command(head, i);
	right = NULL;
	while (*i < list_len && ((t_cmd *)head->content)->id == PIPE)
	{
		cmd = (t_cmd *)head->content;
		head = head->next;
		(*i)++;
		right = pipe_sequence(head, i);
	}
	if (*i < list_len - 1)
		return (left);
	return (create_ast_node(cmd, left, right));
}

t_ast	*complexe_command(t_list *head, int *i)
{
	t_ast			*left;
	t_ast			*right;

	if (head == NULL)
		return (NULL);
	left = NULL;
	right = NULL;
	if (is_redirection((t_cmd *)head->content))
	{
		left = redirection(head, i);
		(*i)++;
		if (head->next)
			right = simple_command(head->next, i);
	}
	else
	{
		left = simple_command(head, i);
		(*i)++;
		if (head->next && is_redirection((t_cmd *)head->next->content))
			right = redirection(head->next, i);
	}
	if (right == NULL)
		return (left);
	return (create_ast_node((t_cmd *)head->content, left, right));
}

t_ast	*simple_command(t_list *head, int *i)
{
	t_ast			*left;
	t_ast			*right;
	t_cmd			*cmd;

	if (head == NULL)
		return (NULL);
	cmd = (t_cmd *)head->content;
	left = NULL;
	if ((t_cmd *)head->content == UNASSIGNED)
		left = cmd_name(head, i);
	right = NULL;
	(*i)++;
	if (((t_cmd *)head->next)->id == UNASSIGNED)
		right = argument(head->next, i);
	return (create_ast_node(cmd, left, right));
}

t_ast	*argument(t_list *head, int *i)
{
	t_ast			*left;
	t_ast			*right;
	t_cmd			*cmd;

	if (head == NULL)
		return (NULL);
	cmd = (t_cmd *)head->content;
	left = NULL;
	if ((t_cmd *)head->content == UNASSIGNED)
		left = cmd_word(head, i);
	right = NULL;
	return (create_ast_node(cmd, left, right));
}

t_ast	*redirection(t_list *head, int *i)
{
	t_ast			*left;
	t_ast			*right;
	t_cmd			*cmd;

	if (head == NULL)
		return (NULL);
	cmd = (t_cmd *)head->content;
	left = NULL;
	if ((t_cmd *)head->content == UNASSIGNED)
		left = cmd_word(head, i);
	right = NULL;
	return (create_ast_node(cmd, left, right));
}
