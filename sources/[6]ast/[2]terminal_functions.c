/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]terminal_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:49:47 by motero            #+#    #+#             */
/*   Updated: 2023/01/13 23:52:47 by motero           ###   ########.fr       */
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
