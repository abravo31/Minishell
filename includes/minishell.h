/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/02/11 00:37:43 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../gnl/get_next_line.h"
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

# define PROMPT_NAME "Minishell > "

/*############################################################################*/
/*                              HEADERS                                       */
/*############################################################################*/

# include "builtin.h"
# include "execution.h"
# include "expander.h"
# include "lexer.h"
# include "parsing.h"
# include "signal_handling.h"
# include "structures.h"
# include "ast.h"
# include "garbage_collector.h"

/*############################################################################*/
/*                              DEBUG FUNCTIONS                               */
/*############################################################################*/

t_list		*hardcode_cmds(void);
void		print_cmd(t_list *head);
void		print2DUtil(t_ast *root, int space);
void		bash(void *content);
void		free_list(t_list *lst, void (*free_content)(void *));

//init_mini
void		free_list(t_list *lst, void (*free_content)(void *));
void		init_minishell(t_minishell *msh);
void		reset_and_free(t_minishell *msh);
void		ft_start_prompt(t_minishell *msh, int tmp_fd_0,
				int tmp_fd_1, int *i);
void		setup_loop(t_minishell *msh, int *tmp_fd_0, int *tmp_fd_1, int *i);

/*############################################################################*/
/*                              STRUCTURES                                    */
/*############################################################################*/

#endif