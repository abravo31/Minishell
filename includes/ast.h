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

#ifndef AST_H
# define AST_H

# include "libft.h"
# include "structures.h"
# include "signal_handling.h"
# include "parsing.h"
# include "garbage_collector.h"
# include "error_management.h"
# include "../gnl/get_next_line.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/*############################################################################*/
/*                              AST FUNCTIONS                                 */
/*############################################################################*/

t_ast		*create_ast_node(t_cmd *cmd, t_ast *left, t_ast *right);

/*############################################################################*/
/*							NOTERMINAL FUNCTIONS                              */
/*############################################################################*/
t_ast		*pipe_sequence(t_list **head, int *i);
t_ast		*complexe_command(t_list **head, int *i);
t_ast		*complexe_command_node(t_ast *left, t_ast *right);
t_ast		*simple_command(t_list **head, int *i);
t_ast		*argument(t_list **head, int *i, t_ast *cmd);

/*############################################################################*/
/*							REDIRECTION FUNCTIONS                             */
/*############################################################################*/
void		init_redirection_function(t_ast *(*redirection_function[4])
				(t_list **, int *));
t_ast		*redirection(t_list **head, int *i);
t_ast		*redirection_left(t_list **head, int *i);
t_ast		*redirection_right(t_list **head, int *i);
t_ast		*redirection_double_left(t_list **head, int *i);
t_ast		*redirection_double_right(t_list **head, int *i);
t_ast		*cmd_filename(t_list **head, int *i);
/*############################################################################*/
/*							TERMINAL FUNCTIONS                              */
/*############################################################################*/
t_ast		*cmd_name(t_list **head, int *i);
t_ast		*cmd_word(t_list **head, int *i);
t_ast		*cmd_redir(t_list **head, int *i);
int			builtin_cmd(t_list **head);
t_ast		*cmd_arg(t_list **head, int *i, t_ast *cmd);
char		**gets_args(t_list *cmd_args);

/*############################################################################*/
/*							AUXILIARY FUNCTIONS                              */
/*############################################################################*/
int			is_redirection(t_cmd *cmd);
t_ast		*create_ast_no_terminal(t_op operator, t_ast *left, t_ast *right);
t_ast		*create_ast_terminal(t_cmd *cmd, t_ast *left, t_ast *right);
void		cmd_arg_loop(t_list *cp_head, t_cmd *word, t_list *cmd_args,
				int *i);
t_ast		*create_terminal_builtin(t_cmd *cmd, t_ast *left, t_ast *right);
t_ast		*create_ast_terminal_w_args(char **args, t_ast *left, t_ast *right);

#endif