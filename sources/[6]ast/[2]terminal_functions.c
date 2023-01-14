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
/* gramamr free table with the terminal functions
cmd_name         : WORD                   
                 ;
cmd_word         : WORD
                 ;
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
