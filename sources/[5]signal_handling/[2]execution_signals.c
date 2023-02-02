/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]execution_signals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:35:40 by motero            #+#    #+#             */
/*   Updated: 2023/02/02 16:22:13 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handling.h"

void	sig_ignore_all(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint_child;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = &handle_sigint_child;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_sig_child(void)
{
	struct sigaction	sa;
	struct sigaction	sa2;

	sa.sa_handler = 0;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa2.sa_handler = 0;
	sigemptyset(&sa2.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_sigint_child(int sig)
{
	if (sig == SIGINT)
	{
		//write(0, "\n", 1);
		printf("\n");
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
	}
}
