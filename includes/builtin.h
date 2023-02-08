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

#ifndef BUILTIN_H
# define BUILTIN_H

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
# endif

# ifndef BUFFER_SIZE_PATH
#  define BUFFER_SIZE_PATH 1024
# endif

# include "libft.h"
# include "structures.h"
# include "error_management.h"
# include "garbage_collector.h"
# include "signal_handling.h"

# include <limits.h>
# include <unistd.h>

/*############################################################################*/
/*                              BUILTIN_FUNCTIONS                             */
/*############################################################################*/

//Search for builtin ft wher in a table and return the corresponding ptr ft
int			execute_builtin(t_minishell *msh, t_ast *root);
//Echo function wth only option-n
int			builtin_echo(t_minishell *msh, t_ast *root);
int			is_flag(char *str);
//cd function with only relative orabsolute path
int			builtin_cd(t_minishell *msh, t_ast *root);
//pwd with no options
int			builtin_pwd(t_minishell *msh, t_ast *root);
//export with no options
int			builtin_export(t_minishell *msh, t_ast *root);
//unset with no options
int			builtin_unset(t_minishell *msh, t_ast *root);
//env with no options or arg 
int			builtin_env(t_minishell *msh, t_ast *root);
// exit with no options
int			builtin_exit(t_minishell *msh, t_ast *root);

/*############################################################################*/
/*                              BUILTIN_FUNCTIONS                             */
/*############################################################################*/
int			is_numeric(char *str);
long long	ft_atoll(const char *nptr);
int			is_big_number(long long num, char *str);
long long	transform_exit_code(char *cmd);

/*############################################################################*/
/*                              ENV MANIPULATION                              */
/*############################################################################*/

char		*getcwd_until_path_fits(void);
void		new_path_empty(t_minishell *msh);
char		*get_env_value_build(t_list *env, char *key);
void		modify_env_value(t_list *env, char *key, char *value);
void		new_path_normal(t_minishell *msh, t_ast *root);
void		list_env_to_char_env(t_minishell *msh);
void		unset_env_value(t_list *env, char *key);
t_env		*new_env(char *key, char *value);
void		export_env_value(t_minishell *msh, t_list *env, char *str);
int			is_valid_export(const char *env);
void		print_sorted_env(t_minishell *msh);
int			str_env_len(char **env);
void		ft_free_tab(char **tab);
void		print_env(char **envp);
void		initilialize_emtpy_env(t_minishell *msh);

#endif