/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]free_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:12:29 by motero            #+#    #+#             */
/*   Updated: 2023/02/05 00:24:41 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	free_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
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

void	free_pid_t_content(void *content)
{
	pid_t	*pid;

	pid = (pid_t *)content;
	free (pid);
}

void	free_double_pointer(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr[i]);
	free(ptr);
}

void	free_env(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}
