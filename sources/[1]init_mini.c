/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]init_mini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:38:23 by motero            #+#    #+#             */
/*   Updated: 2023/02/11 00:43:48 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list *lst, void (*free_content)(void *))
{
	t_list	*current;

	while (lst)
	{
		current = lst;
		lst = lst->next;
		if (free_content)
			free_content((t_cmd *)current->content);
		free(current);
	}
}

void	init_minishell(t_minishell *msh)
{
	msh->status = 1;
	msh->prompt = NULL;
	msh->parsing_error = NULL;
	msh->cmd = NULL;
	msh->cmd_expand = NULL;
	msh->fd_in = -2;
	msh->fd_out = -2;
	msh->pid = NULL;
	msh->env = NULL;
}

void	reset_and_free(t_minishell *msh)
{
	free_garbage_collector(EXCEPT_ENV);
	singleton_heredoc(-1);
	msh->parsing_error = NULL;
	msh->cmd = NULL;
	msh->cmd_expand = NULL;
	msh->root = NULL;
	msh->fd_in = -2;
	msh->fd_out = -2;
	msh->pid = NULL;
	msh->path = NULL;
}

void	ft_start_prompt(t_minishell *msh, int tmp_fd_0, int tmp_fd_1, int *i)
{
	t_list	*head;

	head = msh->cmd_expand;
	msh->root = pipe_sequence(&msh->cmd_expand, i);
	if (!msh->root)
		free_garbage_collector(EXCEPT_ENV);
	add_to_garbage_collector((void *)msh->root, AST);
	msh->cmd_expand = head;
	*i = 0;
	if (singleton_heredoc(0) == 0 && msh->root)
		main_execution(msh, msh->root, i);
	dup2(tmp_fd_0, STDIN_FILENO);
	dup2(tmp_fd_1, STDOUT_FILENO);
	wait_for_children(msh);
	if (msh->parsing_error)
		errors_messages_cases(msh->parsing_error, 99);
}

void	setup_loop(t_minishell *msh, int *tmp_fd_0, int *tmp_fd_1, int *i)
{
	*tmp_fd_0 = dup(STDIN_FILENO);
	*tmp_fd_1 = dup(STDOUT_FILENO);
	add_to_garbage_collector((void *)tmp_fd_0, FD);
	add_to_garbage_collector((void *)tmp_fd_1, FD);
	list_env_to_char_env(msh);
	*i = 0;
	msh->fd_dup[0] = *tmp_fd_0;
	msh->fd_dup[1] = *tmp_fd_1;
	setup_signal_handlers();
	msh->prompt = readline(PROMPT_NAME);
}
