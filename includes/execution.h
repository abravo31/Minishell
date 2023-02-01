/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/01/31 17:47:49 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include "structures.h"
# include "garbage_collector.h"
# include "error_management.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>

/*############################################################################*/
/*                              main decision                                 */
/*############################################################################*/

void		main_execution(t_minishell *msh, t_ast *ast);
void		wait_for_children(t_minishell *msh);

/*############################################################################*/
/*                              no-terminal traveersing						  */
/*############################################################################*/
void		pipe_sequence_traverse(t_minishell *msh, t_ast *root);
void		complex_command_traverse(t_minishell *msh, t_ast *root);
void		simple_command_traverse(t_minishell *msh, t_ast *root);
void		argument_traverse(t_minishell *msh, t_ast *root);
void		redirection_traverse(t_minishell *msh, t_ast *root);
void		simple_builtin_traverse(t_minishell *msh, t_ast *root);
void		complex_builtin_traverse(t_minishell *msh, t_ast *root);

/*############################################################################*/
/*                              no-terminal traveersing						  */
/*############################################################################*/
void		execution_terminal(t_minishell *msh, t_ast *root);	

/*############################################################################*/
/*                              redirections	      						  */
/*############################################################################*/

void		redirect_output(t_minishell *msh, t_ast *root);
void		redirect_input(t_minishell *msh, t_ast *root);
void		redirect_append(t_minishell *msh, t_ast *root);
void		redirect_heredoc(t_minishell *msh, t_ast *root);

/*############################################################################*/
/*                              pid management      						  */
/*############################################################################*/
void		add_pid_to_list(t_minishell *msh, pid_t pid);

/*############################################################################*/
/*                              add to utility	      						  */
/*############################################################################*/
t_list		*allocate_and_store_node(pid_t pid);
char	    **get_char_double_ptr(char *str);
char		*ft_check_access(t_minishell *msh, t_ast *root);
char		**ft_parse_path(char **env);

#endif