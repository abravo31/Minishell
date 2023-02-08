/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/02/08 01:49:50 by motero           ###   ########.fr       */
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

int			fd_errors_out(char *path);
int			fd_errors_in(char *path);
#endif