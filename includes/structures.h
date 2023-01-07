/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/01/07 18:39:52 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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
	BULTINS,
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
	struct s_list	*next;
}					t_list;

typedef struct s_minishell
{
	char	*prompt;
	char	*parsing_error;
	int		status;
	t_list	*cmd;
	t_list	*env;
}	t_minishell;w

#endif