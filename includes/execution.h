/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/02/02 21:40:44 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include "structures.h"
# include "garbage_collector.h"
# include "error_management.h"
# include "signal_handling.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include "../gnl/get_next_line.h"

/*############################################################################*/
/*                              main decision                                 */
/*############################################################################*/

void		main_execution(t_minishell *msh, t_ast *ast, int *i);
void		wait_for_children(t_minishell *msh);

/*############################################################################*/
/*                              pipe traveersing						  	  */
/*############################################################################*/
void		pipe_sequence_traverse(t_minishell *msh, t_ast *root, int *i);
void		child_sequence_traverse(t_minishell *msh, t_ast *root, int *i);
void		parent_seq_traverse(t_minishell *msh, t_ast *root, int *i,
				pid_t pid);

/*############################################################################*/
/*                              no-terminal traveersing						  */
/*############################################################################*/

void		complex_command_traverse(t_minishell *msh, t_ast *root, int *i);
void		simple_command_traverse(t_minishell *msh, t_ast *root, int *i);
void		argument_traverse(t_minishell *msh, t_ast *root, int *i);
void		redirection_traverse(t_minishell *msh, t_ast *root, int *i);
void		simple_builtin_traverse(t_minishell *msh, t_ast *root, int *i);
void		complex_builtin_traverse(t_minishell *msh, t_ast *root, int *i);

/*############################################################################*/
/*                              no-terminal traveersing						  */
/*############################################################################*/
void		execution_terminal(t_minishell *msh, t_ast *root, int *i);	

/*############################################################################*/
/*                              redirections	      						  */
/*############################################################################*/

void		redirect_output(t_minishell *msh, t_ast *root, int *i);
void		redirect_input(t_minishell *msh, t_ast *root, int *i);
void		redirect_append(t_minishell *msh, t_ast *root, int *i);
void		redirect_heredoc(t_minishell *msh, t_ast *root, int *i);

/*############################################################################*/
/*                              pid management      						  */
/*############################################################################*/
void		add_pid_to_list(t_minishell *msh, pid_t pid);

/*############################################################################*/
/*                              add to utility	      						  */
/*############################################################################*/
t_list		*allocate_and_store_node(pid_t pid);
char		**get_char_double_ptr(char *str);
char		*ft_check_access(t_minishell *msh, t_ast *root);
char		*ft_check_direct_path(t_minishell *msh, char *cmd);
char		**ft_parse_path(char **env);

#endif