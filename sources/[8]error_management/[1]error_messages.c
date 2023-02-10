/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]error_messages.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:02:50 by motero            #+#    #+#             */
/*   Updated: 2023/02/11 00:39:41 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_management.h"

void	error_messages_default_cases(char *msg, int error_code)
{
	if (error_code == 201)
		print_error(msg, ": Permission denied", 126);
	else if (error_code == 200)
		print_error(msg, ": Is a directory", 126);
	else if (error_code == 202)
		print_error(msg, ": No such file or directory", 127);
	else if (error_code == 210)
		error_messages_default_cases(msg, fd_errors_out(msg));
	else if (error_code == 211)
		error_messages_default_cases(msg, fd_errors_in(msg));
	else if (error_code == 301)
		print_error(msg, ": Permission denied", 1);
	else if (error_code == 300)
		print_error(msg, ": Is a directory", 1);
	else if (error_code == 302)
		print_error(msg, ": No such file or directory", 1);
	else if (error_code == 127)
		print_error(msg, ": command not found", 127);
	else
		error_messages_special_cases(msg, error_code);
}

void	error_messages_special_cases(char *msg, int error_code)
{
	if (error_code == 99)
		print_error(msg, "", 2);
	else if (error_code == 401)
		print_error(msg, "", 2);
	else if (error_code == 501)
		print_error(msg, " not a valid identifier", 1);
	else
		print_error(msg, "", 1);
}

void	error_message(char	*msg, int error_code)
{
	(void)error_code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	print_error(char	*name, char *msg, int new_code)
{
	g_status = new_code;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

char	*compose_error_message(char *msg1, char *msg2, char *msg3)
{
	char	*msg;
	char	*final_msg;

	msg = ft_strjoin(msg1, msg2);
	if (!msg)
		return (error_safe_exit("malloc error", 99), NULL);
	final_msg = ft_strjoin(msg, msg3);
	free(msg);
	if (!final_msg)
		return (error_safe_exit("malloc error", 99), NULL);
	add_to_garbage_collector((void *)final_msg, INT);
	return (final_msg);
}
