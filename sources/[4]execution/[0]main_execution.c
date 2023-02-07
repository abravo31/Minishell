/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:52:02 by motero            #+#    #+#             */
/*   Updated: 2023/02/06 20:33:55 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	main_execution(t_minishell *msh, t_ast *root, int *i)
{
	if (root == NULL)
		return ;
	// if (*i == -2 && (msh->fd_out == -1 || msh->fd_in == -1))
	// {
	// 	printf("errror occured during fds handlings\n");
	// 	return ;
	// }
	if (root->id->op == PIPE_SEQUENCE)
		pipe_sequence_traverse(msh, root, i);
	else if (root->id->op == COMPLEXE_COMMAND)
		complex_command_traverse(msh, root, i);
	else if (root->id->op == SIMPLE_COMMAND)
		simple_command_traverse(msh, root, i);
	else if (root->id->op == ARGUMENT)
		argument_traverse(msh, root, i);
	else if (root->id->op == REDIRECTION)
		redirection_traverse(msh, root, i);
	else if (root->id->op == SIMPLE_BUILTIN)
		simple_builtin_traverse(msh, root, i);
	else if (root->id->op == CMPLX_BUILT)
		complex_builtin_traverse(msh, root, i);
}

void	execution_terminal(t_minishell *msh, t_ast *root, int *i)
{
	(void)msh;
	if (root == NULL)
		return ;
	printf("%s  ", root->data);
	(void)i;
}

//wait for each child process to finish
void	wait_for_children(t_minishell *msh)
{
	int		status;
	t_list	*current;

	status = 0;
	current = msh->pid;
	while (current)
	{
		waitpid(*(pid_t *)current->content, &status, 0);
		current = current->next;
	}
}

t_list	*allocate_and_store_node(pid_t pid)
{
	t_list	*new;
	pid_t	*content;

	content = malloc(sizeof(pid_t));
	if (content == NULL)
		return (NULL);
	*content = pid;
	new = ft_lstnew(content);
	if (new == NULL)
		return (free(content), NULL);
	return (new);
}

char	**get_char_double_ptr(char *str)
{
	char	**new;

	new = (char **)malloc(sizeof(char *) * 2);
	if (!new)
		error_safe_exit("Allocation error before execve\n");
	new[0] = ft_strdup(str);
	if (!new[0])
	{
		free(new);
		error_safe_exit("Allocation error before execve\n");
	}
	new[1] = NULL;
	return (new);
}
