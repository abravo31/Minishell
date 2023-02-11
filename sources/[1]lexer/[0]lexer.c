/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo31 <abravo31@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:11:15 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/11 15:19:53 by abravo31         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_without_quotes(t_minishell *msh, char prompt, char **str)
{
	if ((is_token(prompt) && *str && !is_token(*str[0]))
		|| (!is_token(prompt) && *str && is_token(*str[0])))
		delimitor(str, msh, 0);
	if ((prompt == '>' || prompt == '<')
		&& *str && *str[0] == '|')
		delimitor(str, msh, 0);
}

void	iter_prompt(t_minishell *msh, char **str, int i)
{
	while (msh->prompt[++i] && !msh->parsing_error)
	{
		check_parsing_errors(msh, 0);
		if (msh->prompt[i] == '$' \
			&& (msh->prompt[i + 1] == '"' || msh->prompt[i + 1] == '\''))
			msh->prompt[i] = ' ';
		if (is_space(msh->prompt[i]))
			delimitor(str, msh, 1);
		else if (!is_space(msh->prompt[i]) && (msh->prompt[i] != '\'' \
		&& msh->prompt[i] != '\"'))
		{
			cmd_without_quotes(msh, msh->prompt[i], str);
			get_char(msh->prompt[i], str);
		}
		else if (msh->prompt[i] == '\'' || msh->prompt[i] == '\"')
		{			
			if ((i > 0 && !is_token(msh->prompt[i - 1]))
				&& !is_space(msh->prompt[i - 1]))
				delimitor(str, msh, 0);
			i = is_quote(msh, i, &msh->prompt, 0);
		}
	}
}

void	pop_nulls(t_list **begin_list)
{
	t_list	*cur;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	cur = *begin_list;
	if (((t_cmd *)(cur->content))->cmd == NULL)
	{
		*begin_list = cur->next;
		free((t_cmd *)(cur->content));
		free(cur);
		pop_nulls(begin_list);
	}
	cur = *begin_list;
	if (cur)
		pop_nulls(&cur->next);
}

// Function to parse cmd from user input
int	get_cmd(t_minishell *msh)
{
	int		i;
	char	*str;	

	i = -1;
	str = NULL;
	iter_prompt(msh, &str, i);
	delimitor(&str, msh, 0);
	check_parsing_errors(msh, 1);
	check_tild(msh);
	if (msh->parsing_error)
		return (0);
	ft_dup_list(msh);
	expanded_cmd_list(msh, msh->cmd_expand);
	ft_join_quote(msh);
	pop_nulls(&msh->cmd_expand);
	return (!msh->parsing_error);
}

// Function to handle space delimitor case
// will create and pus a new node with cmd and it's token
void	delimitor(char **cmd, t_minishell *msh, int space)
{
	t_list	*new;

	if (!*cmd || msh->parsing_error)
		return ;
	if (msh->cmd == NULL)
	{
		msh->cmd = ft_lstnew((void *)new_cmd(*cmd, eval_token(*cmd), space));
		if (!msh->cmd)
			error_safe_exit("Malloc failed", 1);
		add_to_garbage_collector((void *)&msh->cmd, CMD);
	}
	else
	{
		new = ft_lstnew((void *)new_cmd(*cmd, eval_token(*cmd), space));
		if (!new)
		{
			free_garbage_collector(ALL);
			printf("error while adding a delimitor, \
			still not error or way toe xit this function!\n");
			return ;
		}
		ft_lstadd_back(&msh->cmd, new);
	}
	check_parsing_errors(msh, 0);
	*cmd = NULL;
}

// void	__debug_parsing(t_list *cmd)
// {
// 	t_list	*iter;
// 	t_cmd	*current;

// 	iter = cmd;
// 	current = NULL;
// 	while (iter)
// 	{
// 		current = (t_cmd *) iter->content;
// 		printf("(%d){%d}[%s]\n", current->space, current->id, current->cmd);
// 		iter = iter->next;
// 	}
// }
