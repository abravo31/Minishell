/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/02/08 02:40:58 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLING_H
# define SIGNAL_HANDLING_H

# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "parsing.h"
# include "error_management.h"

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif

# ifndef PROMPT_NAME
#  define PROMPT_NAME "minishell"
# endif

/*############################################################################*/
/*                              SIGNAL DURING INTERACTIVE                     */
/*############################################################################*/

// Set up the signal handlers
void		setup_signal_handlers(void);

// Handle the SIGINT signal (ctrl-C)
void		sigint_handler(int sig);

// Handle the EOF signal (ctrl-D)
void		eof_handler(int sig);

// Handle the SIGQUIT signal (ctrl-\)
void		sigquit_handler(int sig);

/*############################################################################*/
/*                              SIGNAL DURING HEREDOC                         */
/*############################################################################*/

void		heredoc_signal_handlers(void);
void		sigquit_heredoc(int sig);

/*############################################################################*/
/*                              SIGNAL DURING EXEC                            */
/*############################################################################*/

void		sig_ignore_all(void);
void		setup_sig_child(void);
void		handle_sigint_child(int sig);

#endif