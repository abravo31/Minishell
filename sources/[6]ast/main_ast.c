/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:31:37 by motero            #+#    #+#             */
/*   Updated: 2023/01/11 20:59:30 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast_node	*create_ast_node(t_cmd *cmd, t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	*node = (t_ast_node *)malloc(sizeof(t_ast_node));
	node->id = cmd->id;
	node->cmd = cmd->cmd;
	node->left = left;
	node->right = right;
	return (node);
}

ast_node	*t_cmd_list_to_ast(t_list *cmd_list, int pos)
{
	t _cmd		*cmd;
	t_cmd		*cmd_suffix;
	ast_node	*left;
	ast_node	*right;
	ast_node	*cmd_name_node;
	ast_node	*cmd_suffix_node;
	t_list		*cmd_suffix_list;

	if (!head)
		return (NULL);
	cmd = (t_cmd *)cmd_list->content;
	if (cmd->id == PIPE)
	{
		left = t_cmd_list_to_ast(head->next, pos + 1);
		right = t_cmd_list_to_ast(head->next, pos + 2);
	}
	return (create_ast_node(cmd, left, right));
	else if (cmd->id == UNASSIGNED || cmd->id == BUILTIN)
	{
		cmd_suffix_list = cmd_list->next;
		cmd_name_node = create_ast_node(cmd, NULL, NULL);
		cmd_suffix_node = NULL;
		while (cmd_suffix_list)
		{
			cmd_suffix = (t_cmd *)cmd_suffix_list->content;
			if (cmd_suffix_node == NULL)
				cmd_suffix_node = create_ast_node(cmd_suffix, NULL, NULL);
			else
				cmd_suffix_node = create_ast_node(cmd_suffix, cmd_suffix_node, NULL);
			cmd_suffix_list = cmd_suffix_list->next;
		}
		return (create_ast_node(NULL, cmd_name_node, cmd_suffix_node));
	}
}
