/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/01/30 23:02:10 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include "libft.h"

/*############################################################################*/
/*                              GARBAGE COLLECTOR                             */
/*############################################################################*/

typedef enum e_memory_type
{
	INT,
	D_INT,
	ENV,
	LST,
	AST,
	CMD,
	FD,
	PID,
}	t_memory_type;

typedef union u_ptr_int
{
	void	*ptr;
	int		val;
}	t_ptr_int;

typedef struct s_mem_block
{
	t_ptr_int		ptr_int;
	t_memory_type	type;
}	t_mem_block;

typedef struct s_garbage_collector
{
	t_list			*ptr;
}	t_garbage_collector;

/*############################################################################*/
/*                              LEXER			                              */
/*############################################################################*/

typedef enum e_token
{
	UNASSIGNED,
	R_REDIR,
	R_DREDIR,
	L_REDIR,
	L_DREDIR,
	PIPE,
	D_QUOTE,
	S_QUOTE,
	WORD,
	BUILTIN,
}	t_token;

typedef struct s_cmd
{
	char	*cmd;
	t_token	id;
}	t_cmd;

/*############################################################################*/
/*                                    AST                                     */
/*############################################################################*/

typedef enum e_operator{
	PIPE_SEQUENCE ,
	COMPLEXE_COMMAND,
	SIMPLE_COMMAND,
	ARGUMENT,
	REDIRECTION,
	SIMPLE_BUILTIN,
	CMPLX_BUILT,
}	t_op;

typedef union id{
	t_op		op;
	t_token		token;
}	t_id;

typedef struct s_ast_node
{
	char				*data;
	int					terminal;	
	t_id				*id;
	struct s_ast_node	*parent;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast;

/*############################################################################*/
/*                             MAIN STRUCTURE                                 */
/*############################################################################*/

typedef struct s_minishell
{
	char	*prompt;
	char	*parsing_error;
	int		status;
	t_list	*cmd;
	t_list	*env;
	t_ast	*root;
	int		fd_out;
	int		fd_in;
	t_list	*pid;
}	t_minishell;

#endif