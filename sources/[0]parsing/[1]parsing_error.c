/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]parsing_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo31 <abravo31@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:18:53 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/05 02:28:21 by abravo31         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Function to check if first token is allowed
int	handle_first_node_error(t_minishell *msh)
{
	size_t				i;
	t_cmd				*first_node;
	static const char	*forbidden_tokens[] = {
		"|",
		NULL,
	};

	i = 0;
	if (!msh->cmd)
		return (0);
	first_node = (t_cmd *)msh->cmd->content;
	while (forbidden_tokens[i])
	{
		if (is_identical((char *) forbidden_tokens[i], first_node->cmd))
		{
			msh->parsing_error = syntax_error(first_node->cmd[0]);
			return (1);
		}
		i++;
	}
	return (0);
}

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
	return (ret);
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
	if (str[pos] && str[pos] == ' ')
		space = 1;
	if (ret)
	{
		t_cmd *cmd = new_cmd(remove_quote(ret), eval_token(ret), space);
		if (cmd == NULL)
			error_safe_exit("Error: cmd is NULL");
		t_list *new = ft_lstnew((void *)cmd);
		if (new == NULL)
			error_safe_exit("Error: list is NULL");
		if (msh->cmd == NULL)
		{
			msh->cmd = new;
			add_to_garbage_collector((void *)&msh->cmd, CMD);
		}
		else
			ft_lstadd_back(&msh->cmd, new);
	}
	free(ret);
	return (pos - 1);
}

// checks if token is unknown
// checks if last node id is an operator
void	check_parsing_errors(t_minishell *msh, int end)
{
	t_list	*iter;
	t_cmd	*current;

	iter = msh->cmd;
	current = NULL;
	if (end && handle_first_node_error(msh))
		return ;
	while (iter)
	{
		current = (t_cmd *) iter->content;
		if (current->cmd && is_token(current->cmd[0]) \
		&& !current->id)
		{
			msh->parsing_error = syntax_error(current->cmd[0]);
			break ;
		}
		if (current->cmd && !iter->next && \
		end && is_token(current->cmd[0]))
			msh->parsing_error = syntax_error('\n');
		else if (current->id >= R_REDIR && current->id <= L_DREDIR && end \
		&& (((t_cmd *)(iter->next->content))->id < D_QUOTE || !iter->next))
			msh->parsing_error = syntax_error(current->cmd[0]);
		iter = iter->next;
	}
}
