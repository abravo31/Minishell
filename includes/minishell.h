/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/01/23 21:36:09 by motero           ###   ########.fr       */
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

/*############################################################################*/
/*                              DEBUG FUNCTIONS                               */
/*############################################################################*/

t_list		*hardcode_cmds(void);
void		print_cmd(t_list *head);
void		print2DUtil(t_ast *root, int space);

/*############################################################################*/
/*                              STRUCTURES                                    */
/*############################################################################*/

#endif