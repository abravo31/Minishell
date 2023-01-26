/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/01/26 22:57:03 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include "structures.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*############################################################################*/
/*                              main decision                                 */
/*############################################################################*/

void		main_execution(t_minishell *msh, t_ast *ast);

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

#endif