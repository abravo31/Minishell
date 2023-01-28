/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]signal_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:38:23 by motero            #+#    #+#             */
/*   Updated: 2023/01/28 18:24:34 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handling.h"

// Set up the signal handlers
/*  																		 **	
** 1-The setup_signal_handlers function first initializes a struct sigaction **
** variable called sigint_action and sets its sa_handler field to the        **
** sigint_handler function. This specifies that the sigint_handler function  **
** should be called when the SIGINT signal (Ctrl+C) is received              **
**  																		 **
** 2- The sigemptyset function is then called to initialize the sa_mask field**
** the sigint_action variable to an empty set of signals. This means that no **
** signals will be blocked (i.e., held pending) when the sigint_handler      **
** function is executed.                                                     **
**  																		 **
** 3-The sigaction function is then called to set the SIGINT signal handler 2** 
** the sigint_action handler. This specifies that the sigint_handler function** 
** should be called when the SIGINT signal is received.                      **
**  																		 **
** 4-The setup_signal_handlers function then repeats the same process for the**
** SIGQUIT (Ctrl+) and SIGTSTP (Ctrl+Z) signals, using the sigquit_handler   **
** and sigtstp_handler functions as the signal handlers, respectively.       **
*/

void	setup_signal_handlers(void)
{
	struct sigaction	sa;
	struct sigaction	quit_sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	quit_sa.sa_handler = SIG_IGN;
	quit_sa.sa_flags = 0;
	sigemptyset(&quit_sa.sa_mask);
	sigaction(SIGQUIT, &quit_sa, NULL);
}

// Handle the SIGINT signal (ctrl-C)
//dnt forget to send  130 error to parents process
void	sigint_handler(int sig)
{
	(void)sig;
	rl_clear_history();
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// Handle the SIGQUIT signal (ctrl-\)
void	sigquit_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_redisplay();
}
