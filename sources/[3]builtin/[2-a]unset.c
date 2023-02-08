
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]ft_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:33:00 by motero            #+#    #+#             */
/*   Updated: 2023/01/09 23:11:51 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

//unset with no options
int	builtin_unset(t_minishell *msh, t_ast *root)
{
	t_list	*env;
	char	**arg;
	int		i;

	if (root->right == NULL)
		return (0);
	if (msh->env == NULL)
		return (0);
	env = msh->env;
	arg = root->right->left->arg;
	i = 1;
	while (arg[i])
	{
		if (arg[i][0] == '-' && ft_strlen(arg[i]) > 1)
			return (errors_messages_cases("unset : invalid option", 401), 1);
		unset_env_value(env, arg[i]);
		i++;
	}
	return (1);
}

void	unset_env_value(t_list *env, char *key)
{
	t_env	*env_var;
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		env_var = tmp->content;
		if (ft_strcmp(env_var->key, key) == 1)
		{
			free(env_var->value);
			env_var->value = NULL;
			free(env_var->key);
			env_var->key = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}
