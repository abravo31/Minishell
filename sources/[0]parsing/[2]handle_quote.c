/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]handle_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo31 <abravo31@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:59:58 by abravo            #+#    #+#             */
/*   Updated: 2023/02/11 15:20:36 by abravo31         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_quote(int d_quo, int s_quo)
{
	if (d_quo && d_quo % 2 == 0)
		return (1);
	if (s_quo && s_quo % 2 == 0)
		return (1);
	return (0);
}

char	*remove_quote(char *quote)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	while (quote[i])
	{
		if (quote[i] != quote[0])
			get_char(quote[i], &ret);
		i++;
	}
	if (!ret)
		return (ft_strdup(""));
	return (ret);
}

void	handle_ret(t_minishell *msh, char *ret, int space)
{
	t_cmd	*cmd;
	t_list	*new;

	cmd = new_cmd(remove_quote(ret), eval_token(ret), space);
	if (cmd == NULL)
		error_safe_exit("Error: cmd is NULL", 1);
	new = ft_lstnew((void *)cmd);
	if (new == NULL)
		error_safe_exit("Error: list is NULL", 1);
	if (msh->cmd == NULL)
	{
		msh->cmd = new;
		add_to_garbage_collector((void *)&msh->cmd, CMD);
	}
	else
		ft_lstadd_back(&msh->cmd, new);
	free(ret);
}

int	is_quote(t_minishell *msh, int pos, char **cmd, int space)
{
	int		d_quo;
	int		s_quo;
	char	*str;
	char	*ret;

	str = *cmd;
	ret = NULL;
	d_quo = 0;
	s_quo = 0;
	while (str[pos] && !end_quote(d_quo, s_quo))
	{
		if (str[pos] == '\"' && s_quo % 2 == 0)
			d_quo++;
		if (str[pos] == '\'' && d_quo % 2 == 0)
			s_quo++;
		get_char(str[pos++], &ret);
	}
	if (!end_quote(d_quo, s_quo))
		msh->parsing_error = syntax_error('\n');
	if (str[pos] && is_space(str[pos]))
		space = 1;
	if (ret)
		handle_ret(msh, ret, space);
	return (pos - 1);
}
