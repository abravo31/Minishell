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

/*############################################################################*/
/*                              AST FUNCTIONS                                 */
/*############################################################################*/

t_ast	*create_ast_node(t_cmd *cmd, t_ast *left, t_ast *right);
t_ast	*t_cmd_list_to_ast(t_list *cmd_list, int pos);
void	print_ast(t_ast *root, int level);

/*############################################################################*/
/*							NOTERMINAL FUNCTIONS                              */
/*############################################################################*/
t_ast	*pipe_sequence(t_list *head, int *i);
t_ast	*complexe_command(t_list *head, int *i);
t_ast	*simple_command(t_list *head, int *i);
t_ast	*argument(t_list *head, int *i);
t_ast	*redirection(t_list *head, int *i);

/*############################################################################*/
/*							TERMINAL FUNCTIONS                              */
/*############################################################################*/
t_ast	*cmd_name(t_list *head, int *i);
t_ast	*cmd_word(t_list *head, int *i);

/*############################################################################*/
/*							AUXILIARY FUNCTIONS                              */
/*############################################################################*/
size_t	ft_lstlen(t_list *lst);
int		is_redirection(t_cmd *cmd);
void	print2DUtil(t_ast *root, int space);

#endif