/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/01/07 17:04:29 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "libft.h"
# include "structures.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

/*############################################################################*/
/*                            GARBAGE COLLECTOR FUNCTIONS                     */
/*############################################################################*/

t_garbage_collector	**singleton_garbage_collector(void);
void				init_garbage_collector(void);
void				add_to_garbage_collector(void *ptr, t_memory_type type);

/*############################################################################*/
/*                            GARBAGE COLLECTOR FREE BLOCKS                   */
/*############################################################################*/

void				free_garbage_collector(void);
void				free_all_blocks(t_garbage_collector *gc);
void				free_block(t_mem_block *block);
void				close_fd(t_mem_block *block);

/*############################################################################*/
/*                            SPECIALIZED FREE FUNCTIONS                      */
/*############################################################################*/

void				free_cmd(void *content);
void				free_ast(t_ast *root);
void				free_pid_t_content(void *content);
void				free_double_pointer(void **ptr);
#endif