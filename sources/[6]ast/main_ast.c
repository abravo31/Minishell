/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:31:37 by motero            #+#    #+#             */
/*   Updated: 2023/01/13 21:15:51 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
Grammar table being a grammar-free parser

pipe_sequence    : complexe_command
                 | complexe_command '|' pipe_sequence
                 ;
complexe_command : simple_command 
				 | simple_command  redirection
				 | redirection	simple_command
simple_command	: cmd_name
				| cmd_name argument
				;
argument		: cmd_word
				| cmd_word cmd_word
cmd_name         : WORD                   
                 ;
cmd_word         : WORD
                 ;
redirection 	: '<' WORD
				| '>' WORD
				| '<<' WORD
				| '>>' WORD
				;
*/

void	print_ast(t_ast *root, int level)
{
	if (root == NULL)
		return ;
	for (int i = 0; i < level; i++) ft_printf("\t");
	ft_printf("%s\n", root->data);
	print_ast(root->left, level + 1);
	print_ast(root->right, level + 1);
}

t_ast	*create_ast_node(t_cmd *cmd, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (cmd)
	{
		node->id->token = cmd->id;
		node->data = cmd->cmd;
		node->left = left;
		node->right = right;
	}
	return (node);
}

t_ast	*t_cmd_list_to_ast(t_list *cmd_list, int pos)
{
	t_cmd		*cmd;
	t_cmd		*cmd_suffix;
	t_ast		*left;
	t_ast		*right;
	t_ast		*cmd_name_node = NULL;
	t_ast		*cmd_suffix_node;
	t_list		*cmd_suffix_list;

	if (!cmd_list)
		return (NULL);
	ft_printf("STARFOULA?\n");
	cmd = (t_cmd *)cmd_list->content;
	ft_printf("STARFOULA twos?\n");
	if (cmd->id == PIPE)
	{
		ft_printf("THERE IS  PIPE");
		left = t_cmd_list_to_ast(cmd_list->next, pos);
		right = t_cmd_list_to_ast(cmd_list->next, pos + 1);
		return (create_ast_node(cmd, left, right));
	}
	else if (cmd->id == UNASSIGNED || cmd->id == BUILTIN)
	{
		cmd_suffix_list = cmd_list->next;
		cmd_name_node = create_ast_node(cmd, NULL, NULL);
		cmd_suffix_node = NULL;
		ft_printf("command");
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
	return (cmd_name_node);
}
