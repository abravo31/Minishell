/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:02:50 by motero            #+#    #+#             */
/*   Updated: 2023/02/07 21:49:48 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_management.h"

void	error_safe_exit(char *msg, int error_code)
{
	g_status = error_code;
	if (error_code == errno)
		g_status = errno;
	if (g_status == 126)
		print_error(msg, ": Is a directory");
	else if (g_status == 127)
	{
		ft_putstr_fd("\nminishell: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": command not found", 2);
	}
	else
		perror(msg);
	free_garbage_collector(ALL);
	exit(g_status);
}

void	error_message(char	*msg, int error_code)
{
	(void)error_code;
	ft_putstr_fd("\nminishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	print_error(char	*name, char *msg)
{
	ft_putstr_fd("\nminishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
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
		if (WIFSIGNALED(status) && WTERMSIG(status) == 2)
			ft_putstr_fd("\n", 2);
		else if (WIFSIGNALED(status) && WTERMSIG(status) == 3)
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
	//perror(strerror(g_status));
	if (g_status == 13 || g_status == 21)
		g_status = 1;
	else if (g_status == 1)
		ft_putstr_fd("error detected/!\n", 2);
	printf("g_status = %d\n", g_status);
}
