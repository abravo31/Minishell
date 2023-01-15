/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]terminal_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:49:47 by motero            #+#    #+#             */
/*   Updated: 2023/01/14 21:29:13 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
/* 
Terminal operators are the leaf nodes of an Abstract Syntax Tree (AST).
 They represent the smallest units of input in the language being parsed. 
 In this case, the terminal operators are:

cmd_name, which represents a single word
cmd_word, which represents a single word in an argument
cmd_redir, which represents a redirection operator (<, >, <<, >>)
These terminal operators are defined in the grammar table as follows:
gramamr free table with the terminal functions
cmd_name         : WORD                   
                 ;
cmd_word         : WORD
                 ;
cdm_redir        : '<' cmd_word
				 |  cmd_word '>' 
				 | '<<' cmd_word
				 |  cmd_word '>>' 
				 ;
*/

/*
 This function is used to extract the command name from the input list 
 and create an AST node for it.
*/
t_ast	*cmd_name(t_list **head, int *i)
{
	t_cmd	*cmd;

	if ((*head) == NULL)
		return (NULL);
	cmd = (t_cmd *)(*head)->content;
	if (cmd->id == UNASSIGNED)
	{
		(*i)++;
		(*head) = (*head)->next;
		return (create_ast_terminal(cmd, NULL, NULL));
	}
	return (NULL);
}

/*
This function is used to extract the command word from the input list
 and create an AST node for it. It also handles the case where multiple 
 words are present.
*/
t_ast	*cmd_word(t_list **head, int *i)
{
	t_cmd	*cmd;
	t_cmd	*first_word;

	if ((*head) == NULL)
		return (NULL);
	first_word = (t_cmd *)(*head)->content;
	cmd = (t_cmd *)(*head)->content;
	while ((*head) && cmd->id == UNASSIGNED)
	{
		(*i)++;
		(*head) = (*head)->next;
		if ((*head) == NULL)
			break ;
		cmd = (t_cmd *)(*head)->content;
	}
	return (create_ast_terminal(first_word, NULL, NULL));
}

/*
This function is used to extract the redirection operator from the
input list and create an AST node for it. It checks if the current
element in the input list is a redirection operator.
*/
t_ast	*cmd_redir(t_list **head, int *i)
{
	t_cmd	*cmd;

	if ((*head) == NULL)
		return (NULL);
	cmd = (t_cmd *)(*head)->content;
	if (is_redirection(cmd))
	{
		(*i)++;
		(*head) = (*head)->next;
		return (create_ast_terminal(cmd, NULL, NULL));
	}
	return (NULL);
}
