/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/02/11 00:35:25 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MANAGEMENT_H
# define ERROR_MANAGEMENT_H

# include "libft.h"
# include "structures.h"
# include "garbage_collector.h"
# include "execution.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>

extern int	g_status;

/*############################################################################*/
/*                              error display                                 */
/*############################################################################*/

void		wait_for_children(t_minishell *msh);
void		error_safe_exit(char *msg, int error_code);
void		print_error(char	*name, char *msg, int new_code);
void		error_message(char	*name, int error_code);
void		error_management(t_list *current);
void		error_messages_default_cases(char *msg, int error_code);
void		error_messages_special_cases(char *msg, int error_code);
char		*compose_error_message(char *msg1, char *msg2, char *msg3);
int			fd_errors_out(char *path);
int			fd_errors_in(char *path);
#endif