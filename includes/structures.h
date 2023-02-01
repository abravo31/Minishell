/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/02/01 23:29:03 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdlib.h>
# include "libft.h"

/*############################################################################*/
/*                              STRUCTURES                                    */
/*############################################################################*/

typedef enum e_memory_type
{
	INT,
	D_INT,
	ENV,
	LST,
	AST,
	CMD,
}	t_memory_type;

typedef struct s_mem_block
{
	void			*ptr;
	t_memory_type	type;
}	t_mem_block;

typedef struct s_garbage_collector
{
	t_list			*ptr;
}	t_garbage_collector;

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
	int		space;
	t_token	id;
}	t_cmd;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

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

typedef struct s_minishell
{
	char	*prompt;
	char	*parsing_error;
	int		status;
	t_list	*cmd;
	t_list	*cmd_expand;
	t_list	*env;
	t_ast	*root;
	t_list	*fd;
}	t_minishell;

#endif