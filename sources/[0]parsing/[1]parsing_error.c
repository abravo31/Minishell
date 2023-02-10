/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]parsing_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:18:53 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/10 21:13:39 by abravo           ###   ########.fr       */
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
		end && current->id > UNASSIGNED && current->id <= PIPE)
			msh->parsing_error = syntax_error('\n');
		else if (current->id >= R_REDIR && current->id <= L_DREDIR && end \
		&& (((t_cmd *)(iter->next->content))->id < D_QUOTE || !iter->next))
			msh->parsing_error = syntax_error(current->cmd[0]);
		iter = iter->next;
	}
}

//Function to display syntax error at character where.
char	*syntax_error(char where)
{
	char	*ret;

	if (where == '\n')
	{
		ret = ft_strdup("syntax error near unexpected token \'newline\'");
		if (!ret)
			return (NULL);
		add_to_garbage_collector((void *)ret, INT);
		return (ret);
	}
	ret = ft_strdup("syntax error near unexpected token \'?\'");
	if (!ret)
		return (NULL);
	add_to_garbage_collector((void *)ret, INT);
	ret[ft_strlen(ret) - 2] = where;
	return (ret);
}
