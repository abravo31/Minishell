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

# include "libft.h"

/*############################################################################*/
/*                              BUILTIN_FUNCTIONS                             */
/*############################################################################*/

//Search for builtin funtion wereinina table and return the corresponding ptr ft
int	execute_builtin(t_cmd *cmd);
//Echo function wth only option-n
int	builtin_echo(t_cmd *cmd);
//cd function with only relative orabsolute path
int	builtin_cd(t_cmd *cmd);
//pwd with no options
int	builtin_pwd(t_cmd *cmd);
//export with no options
int	builtin_export(t_cmd *cmd);
//unset with no options
int	builtin_unset(t_cmd *cmd);
//env with no options or arg 
int	builtin_env(t_cmd *cmd);
// exit with no options
int	builtin_exit(t_cmd *cmd);

#endif