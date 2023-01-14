/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:31:37 by motero            #+#    #+#             */
/*   Updated: 2023/01/14 17:49:06 by motero           ###   ########.fr       */
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
	node->id = malloc(sizeof(t_id));
	if (cmd)
	{
		//ft_printf("cmd->id = %s\n", cmd->id);
		node->id->token = cmd->id;
		node->data = cmd->cmd;
		node->left = left;
		node->right = right;
	}
	return (node);
}
