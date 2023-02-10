/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/02/10 21:44:34 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "structures.h"
# include "signal_handling.h"
# include "garbage_collector.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../gnl/get_next_line.h"

/*############################################################################*/
/*                              STRUCTURES                                    */
/*############################################################################*/
void	here_doc(t_cmd *cmd, int *i);
int		singleton_heredoc(int i);
char	*heredoc_init(t_cmd *cmd, int *i, char **delimiter, int *tmp);
void	unlink_heredoc(char *tmp_name, t_cmd *cmd);
void	terminate_heredoc(char *line, char *tmp_name, t_cmd *cmd,
			char *delimiter);
#endif