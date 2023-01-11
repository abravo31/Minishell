/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:31:37 by motero            #+#    #+#             */
/*   Updated: 2023/01/11 18:46:08 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

ast_node	*t_cmd_list_to_ast(t_list *head, int pos)
{
	t _cmd		*cmd;
	ast_node	*new_node;

	if (!head)
		return (NULL);
	cmd = (t_cmd *)head->content;
	new_node = NULL;
	if (cmd->id == CMD_NAME || cmd->id == CM_WORD)
	{
		new_node = create_cmd_node(cmd);
		new_node
	}

}
