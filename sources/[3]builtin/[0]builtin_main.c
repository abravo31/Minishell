/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]builtin_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:14:51 by motero            #+#    #+#             */
/*   Updated: 2023/02/07 21:10:38 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "structures.h"

int	execute_external(t_minishell *msh, t_ast *root)
{
	(void)msh;
	(void)root;
	return (printf("Execute external\n"));
}

static void	init_builtin_functions(int (**builtin_functions)(t_minishell *msh,
	t_ast *root))
{
	builtin_functions[0] = &builtin_echo;
	builtin_functions[1] = &builtin_cd;
	builtin_functions[2] = &builtin_pwd;
	builtin_functions[3] = &builtin_export;
	builtin_functions[4] = &builtin_unset;
	builtin_functions[5] = &builtin_env;
	builtin_functions[6] = &builtin_exit;
}

int	execute_builtin(t_minishell *msh, t_ast *root)
{
	char const	*builtins[7]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			(*builtin_functions[7])(t_minishell *, t_ast *);
	int const	nbr_builtins = sizeof(builtins) / sizeof(char const *);
	int			i;
	char		*cmd;

	cmd = root->left->data;
	if (!cmd)
		error_safe_exit("builtin is NULL\n", 1);
	init_builtin_functions(builtin_functions);
	i = 0;
	while (i < nbr_builtins)
	{
		if (ft_strcmp(cmd, builtins[i]) == 1)
			return ((*builtin_functions[i])(msh, root));
		i++;
	}
	return (execute_external(msh, root));
}
