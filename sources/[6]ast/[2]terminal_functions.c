/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]terminal_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:49:47 by motero            #+#    #+#             */
/*   Updated: 2023/01/14 00:08:04 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
/* gramamr free table with the terminal functions
cmd_name         : WORD                   
                 ;
cmd_word         : WORD
                 ;
*/

t_ast	*cmd_name(t_list *head, int *i)
{
	t_cmd	*cmd;

	if (head == NULL)
		return (NULL);
	cmd = (t_cmd *)head->content;
	if (cmd->id == UNASSIGNED)
	{
		(*i)++;
		return (create_ast_node(cmd, NULL, NULL));
	}
	return (NULL);
}

t_ast	*cmd_word(t_list *head, int *i)
{
	t_cmd	*cmd;
	t_cmd	*first_word;

	if (head == NULL)
		return (NULL);
	first_word = (t_cmd *)head->content;
	cmd = (t_cmd *)head->content;
	while (cmd->id == UNASSIGNED)
	{
		(*i)++;
		head = head->next;
	}
	return (create_ast_node(first_word, NULL, NULL));
}