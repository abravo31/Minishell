/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo31 <abravo31@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:11:15 by abravo31          #+#    #+#             */
/*   Updated: 2023/02/08 14:26:43 by abravo31         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	iter_prompt(t_minishell *msh, char **str, int i)
{
	while (msh->prompt[++i] && !msh->parsing_error)
	{
		check_parsing_errors(msh, 0);
		if (msh->prompt[i] == ' ')
			delimitor(str, msh, 1);
		else if (msh->prompt[i] != ' ' && (msh->prompt[i] != '\'' \
		&& msh->prompt[i] != '\"'))
		{
			if ((is_token(msh->prompt[i]) && *str && !is_token(*str[0]))
				|| (!is_token(msh->prompt[i]) && *str && is_token(*str[0])))
				delimitor(str, msh, 0);
			if ((msh->prompt[i] == '>' || msh->prompt[i] == '<') \
			&& *str && *str[0] == '|')
				delimitor(str, msh, 0);
			get_char(msh->prompt[i], str);
		}
		else if (msh->prompt[i] == '\'' || msh->prompt[i] == '\"')
		{			
			if (i > 0 && !is_token(msh->prompt[i - 1]) \
			&& msh->prompt[i - 1] != ' ')
				delimitor(str, msh, 0);
			i = is_quote(msh, i, &msh->prompt, 0);
		}
	}
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
	expanded_cmd_list(msh);
	ft_dup_list(msh);
	//add_to_garbage_collector((void *)&msh->cmd_expand, CMD);
	ft_join_quote(msh);
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
			printf("error while adding a delimitor, but you forgot to free!\n");
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

// Function that returns 1 or 0 weither c is a token or not
int	is_token(char c)
{
	size_t				i;
	static const char	*tokens[] = {
		">",
		"<",
		"|",
		NULL,
	};

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == c)
			return (1);
		i++;
	}
	return (0);
}

// Function to return corresponding token from string
t_token	eval_token(char *cmd)
{
	if (cmd[0] == '\"')
		return (D_QUOTE);
	if (cmd[0] == '\'')
		return (S_QUOTE);
	if (is_identical(">", cmd))
		return (R_REDIR);
	else if (is_identical(">>", cmd))
		return (R_DREDIR);
	else if (is_identical("<", cmd))
		return (L_REDIR);
	else if (is_identical("<<", cmd))
		return (L_DREDIR);
	else if (is_identical("|", cmd))
		return (PIPE);
	else if (!is_token(cmd[0]))
		return (WORD);
	return (UNASSIGNED);
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
