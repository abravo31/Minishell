/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo31 <abravo31@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/02/09 04:02:06 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "structures.h"
# include "libft.h"
# include "garbage_collector.h"
# include "builtin.h"

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

/*############################################################################*/
/*                               ENV FUNCTIONS                                */
/*############################################################################*/

void		get_env(char **env, t_minishell *msh);
void		expanded_cmd_list(t_minishell *msh, t_list *cmd);
char		*get_env_value(int *index, t_minishell *msh, char *str);
char		*get_value_from_key(t_minishell *msh, char *key);
void		ft_dup_list(t_minishell *msh);
void		ft_join_quote(t_minishell *msh);
t_env		*new_env(char *key, char *value);
void		check_tild(t_minishell *msh);
void		increment_shlvl(t_minishell *msh);
void		create_add_shlvl(t_minishell *msh);
void		__debug_env(t_minishell *msh);
char		**ft_split_expand(char const *s);
size_t		ft_nbr_clm(char const *s);
void        insert_to_list(int i, char *insert, t_list **iter);

#endif