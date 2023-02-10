/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:02:50 by motero            #+#    #+#             */
/*   Updated: 2023/02/11 00:37:10 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_management.h"

void	error_safe_exit(char *msg, int error_code)
{
	g_status = error_code;
	if (error_code == errno)
		g_status = errno;
	error_messages_default_cases(msg, g_status);
	free_garbage_collector(ALL);
	rl_clear_history();
	exit(g_status);
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
		if (waitpid(*(pid_t *)current->content, &status, 0) < 0)
			break ;
		if (WTERMSIG(status) == 2)
			ft_putstr_fd("\n", 1);
		else if (WTERMSIG(status) == 3)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		error_management(current);
		current = current->next;
	}
}

void	error_management(t_list *current)
{
	(void)current;
	if (g_status == 13 || g_status == 21)
		g_status = 1;
}

int	fd_errors_out(char *path)
{
	if (is_directory(path))
		return (300);
	if (access(path, F_OK))
		return (302);
	if (access(path, W_OK))
		return (301);
	return (201);
}

int	fd_errors_in(char *path)
{
	if (access(path, F_OK))
		return (302);
	if (access(path, R_OK))
		return (301);
	return (201);
}
