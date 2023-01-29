/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main_garbge_collector.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:12:29 by motero            #+#    #+#             */
/*   Updated: 2023/01/29 18:12:05 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	free_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	printf("cmd to erase %s\n", cmd->cmd);
	free(cmd->cmd);
	free(cmd);
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