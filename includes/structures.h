/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/01/14 17:49:10 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdlib.h>

/*############################################################################*/
/*                              STRUCTURES                                    */
/*############################################################################*/

typedef enum e_token
{
	UNASSIGNED,
	R_REDIR,
	R_DREDIR,
	L_REDIR,
	L_DREDIR,
	PIPE,
	BUILTIN,
	D_QUOTE,
	S_QUOTE,
}	t_token;

typedef struct s_cmd
{
	char	*cmd;
	t_token	id;
}	t_cmd;

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef enum e_operator{
	PIPE_SEQUENCE ,
	COMPLEXE_COMMAND,
	SIMPLE_COMMAND,
	ARGUMENT,
	REDIRECTION,
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
	t_list	*env;
	t_ast	*root;
}	t_minishell;

#endif