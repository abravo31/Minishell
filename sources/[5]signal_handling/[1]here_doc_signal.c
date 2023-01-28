/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]here_doc_signal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:35:40 by motero            #+#    #+#             */
/*   Updated: 2023/01/27 23:42:32 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handling.h"

/* Handle the SIGINT signal (ctrl-C) during heredoc
** It calls singleton to set the heredoc flag to 1
*/
static void	signint_heredoc(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	(void)sig;
	singleton_heredoc(1);
	//printf("\n");
}

void	heredoc_signal_handlers(void)
{
	struct sigaction	sa;
	//struct sigaction	quit_sa;

	sa.sa_sigaction = &signint_heredoc;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, 0);
}


