/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]signal_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:38:23 by motero            #+#    #+#             */
/*   Updated: 2023/01/09 23:37:26 by motero           ###   ########.fr       */
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
	struct sigaction	eof_sa;
	struct sigaction	quit_sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	eof_sa.sa_handler = eof_handler;
	sigemptyset(&eof_sa.sa_mask);
	eof_sa.sa_flags = 0;
	sigaction(EOF, &eof_sa, NULL);
	quit_sa.sa_handler = sigquit_handler;
	sigemptyset(&quit_sa.sa_mask);
	quit_sa.sa_flags = 0;
	sigaction(SIGQUIT, &quit_sa, NULL);
}

// Handle the SIGINT signal (ctrl-C)
void	sigint_handler(int sig)
{
	(void)sig;
	ft_printf("\n%s", PROMPT_NAME);
	write(STDOUT_FILENO, "", 1);
}

// Handle the EOF signal (ctrl-D)
void	eof_handler(int sig)
{
	(void)sig;
}

// Handle the SIGQUIT signal (ctrl-\)
void	sigquit_handler(int sig)
{
	(void)sig;
	exit(EXIT_SUCCESS);
}
