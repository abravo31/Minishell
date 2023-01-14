/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [3]auxiliary_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:33:27 by motero            #+#    #+#             */
/*   Updated: 2023/01/14 18:02:58 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

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

int	is_redirection(t_cmd *cmd)
{
	return (cmd->id == L_REDIR
		|| cmd->id == L_DREDIR
		|| cmd->id == R_REDIR
		|| cmd->id == R_DREDIR);
}

void	print2DUtil(t_ast *root, int space)
{
	char const	*operators[] = {"PIPE_SEQUENCE", "COMPLEXE_COMMAND", "SIMPLE_COMMAND", "ARGUMENT", "REDIRECTION"};
	char const	*tokens[] = {"UNASSIGNED", "R_REDIR", "R_DREDIR", "L_REDIR", "L_DREDIR", "PIPE", "BUILTIN", "D_QUOTE", "S_QUOTE"};

	if (root == NULL)
		return ;
	space += 10;
	print2DUtil(root->right, space);
	ft_printf("\n");
	for (int i = 10; i < space; i++)
		ft_printf(" ");
	if (root->terminal)
	{
		ft_printf("%s\n", tokens[root->id->token]);
		ft_printf("%s\n", root->data);
	}
	else
		ft_printf("%s\n", operators[root->id->op]);
	print2DUtil(root->left, space);
}

t_ast	*create_ast_no_terminal(t_op operator, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	node->id = malloc(sizeof(t_id));
	node->terminal = 0;
	node->id->op = operator;
	node->data = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*create_ast_terminal(t_cmd *cmd, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	node->id = malloc(sizeof(t_id));
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