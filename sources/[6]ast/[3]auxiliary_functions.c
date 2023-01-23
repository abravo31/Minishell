/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3]auxiliary_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:33:27 by motero            #+#    #+#             */
/*   Updated: 2023/01/14 19:16:03 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
calculates and returns the number of elements in a linked list
*/
size_t	ft_lstlen(t_list *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

/*
checks if a given command is a redirection operator
*/
int	is_redirection(t_cmd *cmd)
{
	return (cmd->id == L_REDIR
		|| cmd->id == L_DREDIR
		|| cmd->id == R_REDIR
		|| cmd->id == R_DREDIR);
}

/*
creates a non-terminal node in an abstract syntax tree,
with the given operator and left/right child nodes
*/
t_ast	*create_ast_no_terminal(t_op operator, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->id = malloc(sizeof(t_id));
	if (node->id == NULL)
		return (free(node), NULL);
	node->terminal = 0;
	node->id->op = operator;
	node->data = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

/*
creates a terminal node in an abstract syntax tree, with the given
command, and left/right child nodes.
*/
t_ast	*create_ast_terminal(t_cmd *cmd, t_ast *left, t_ast *right)
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
		node->terminal = 1;
		node->id->token = cmd->id;
		node->data = cmd->cmd;
		node->left = left;
		node->right = right;
	}
	return (node);
}