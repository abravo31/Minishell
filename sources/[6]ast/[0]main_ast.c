/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:31:37 by motero            #+#    #+#             */
/*   Updated: 2023/01/28 19:14:56 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
Grammar table being a grammar-free parser

pipe_sequence    : complexe_command
                 | complexe_command '|' pipe_sequence
                 ;
complexe_command : simple_command 
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

/*
This function creates a new node for an abstract syntax tree (AST) and
initializes it with the provided information. It allocates memory for the node,
sets its id and data fields, and sets its left and right child pointers to the
provided left and right child nodes. The function also handle the case where
the cmd parameter is null and handle the memory allocation .
*/
t_ast	*create_ast_node(t_cmd *cmd, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->id = malloc(sizeof(t_id));
	if (node->id == NULL)
		return (free(node), NULL);
	if (cmd)
	{
		node->id->token = cmd->id;
		node->data = cmd->cmd;
		node->left = left;
		node->right = right;
	}
	return (node);
}

/*
This function takes the root of the AST as its parameter. 
It checks if the root is NULL, if it is, it returns.
Else it recursively frees the left and right subtrees of the root,
then it frees the id field and finally the root itself.
*/
void	free_ast(t_ast *root)
{
	if (root == NULL)
		return ;
	free_ast(root->left);
	free_ast(root->right);
	free(root->id);
	free(root);
}
