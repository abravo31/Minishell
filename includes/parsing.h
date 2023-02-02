/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/02/02 19:03:16 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "structures.h"
# include "signal_handling.h"

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

#endif