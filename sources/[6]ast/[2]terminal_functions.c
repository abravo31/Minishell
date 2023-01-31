/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [2]terminal_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 23:49:47 by motero            #+#    #+#             */
/*   Updated: 2023/01/31 19:24:55 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
/* 
Terminal operators are the leaf nodes of an Abstract Syntax Tree (AST).
 They represent the smallest units of input in the language being parsed. 
 In this case, the terminal operators are:

cmd_name, which represents a single word
cmd_word, which represents a single word in an argument
cmd_redir, which represents a redirection operator (<, >, <<, >>)
These terminal operators are defined in the grammar table as follows:
gramamr free table with the terminal functions
cmd_name         : WORD                   
                 ;
cmd_word         : WORD
                 ;
cdm_redir        : '<' cmd_word
				 |  cmd_word '>' 
				 | '<<' cmd_word
				 |  cmd_word '>>' 
				 ;
*/

/*
 This function is used to extract the command name from the input list 
 and create an AST node for it.
*/
t_ast	*cmd_name(t_list **head, int *i)
{
	t_cmd	*cmd;
	int		builtin;

	if ((*head) == NULL)
		return (NULL);
	cmd = (t_cmd *)(*head)->content;
	builtin = 0;
	if (cmd->id == WORD)
	{
		builtin = builtin_cmd(head);
		(*i)++;
		(*head) = (*head)->next;
		if (builtin)
			return (create_terminal_builtin(cmd, NULL, NULL));
		return (create_ast_terminal(cmd, NULL, NULL));
	}
	return (NULL);
}

/*
This function is used to extract the command word from the input list
 and create an AST node for it. It also handles the case where multiple 
 words are present.
*/
t_ast	*cmd_word(t_list **head, int *i)
{
	t_cmd	*cmd;
	t_cmd	*first_word;

	if ((*head) == NULL)
		return (NULL);
	first_word = (t_cmd *)(*head)->content;
	cmd = (t_cmd *)(*head)->content;
	while ((*head) && cmd->id == WORD)
	{
		(*i)++;
		(*head) = (*head)->next;
		if ((*head) == NULL)
			break ;
		cmd = (t_cmd *)(*head)->content;
	}
	return (create_ast_terminal(first_word, NULL, NULL));
}

/* Function that will create a terminal node , but this time it will
** be a t_arg structure instead of a t_cmd structure. This is used
** in the execve function to pass the arguments to the program in 
** the form of a char **arg.
** args: is the name of the command comming fom thr t_ast *cmd
** As long as we find a word we will add it to the  char **arg
*/
t_ast	*cmd_arg(t_list **head, int *i, t_ast *cmd)
{
	t_cmd	*word;
	t_list	*cmd_args;
	t_list	*current;
	char	*tmp;
	char	**arg;

	if ((*head) == NULL)
		return (NULL);
	tmp = ft_strdup(cmd->data);
	cmd_args = ft_lstnew(tmp);
	if (!cmd_args)
		error_safe_exit("Malloc failed in cmd_arg");
	word = (t_cmd *)(*head)->content;
	while ((*head) && word->id == WORD)
	{
		tmp = ft_strdup(word->cmd);
		ft_lstadd_back(&cmd_args, ft_lstnew(tmp));
		(*i)++;
		(*head) = (*head)->next;
		if ((*head) == NULL)
			break ;
		word = (t_cmd *)(*head)->content;
	}
	int	j;
	j = 0;
	arg = ft_calloc(sizeof(char *), (ft_lstsize(cmd_args) + 1));
	if (!arg)
		error_safe_exit("Malloc failed in cmd_arg");
	add_to_garbage_collector(arg, D_INT);
	current = cmd_args;
	while (current)
	{
		arg[j] = ft_strdup(current->content);
		if (!arg[j])
		{
			ft_lstclear(&cmd_args, free);
			error_safe_exit("Malloc failed in cmd_arg");
		}
		current = current->next;
		j++;
	}
	arg[j] = NULL;
	ft_lstclear(&cmd_args, free);
	return (create_ast_terminal_w_args(arg, NULL, NULL));
}


/*
This function is used to extract the redirection operator from the
input list and create an AST node for it. It checks if the current
element in the input list is a redirection operator.
*/
t_ast	*cmd_redir(t_list **head, int *i)
{
	t_cmd	*cmd;

	if ((*head) == NULL)
		return (NULL);
	cmd = (t_cmd *)(*head)->content;
	if (is_redirection(cmd))
	{
		(*i)++;
		(*head) = (*head)->next;
		return (create_ast_terminal(cmd, NULL, NULL));
	}
	return (NULL);
}

int	builtin_cmd(t_list **head)
{
	t_cmd		*cmd;
	int			i;
	char const	*builtins[7]
		= {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int const	nbr_builtins = sizeof(builtins) / sizeof(char const *);

	if ((*head) == NULL)
		return (0);
	cmd = (t_cmd *)(*head)->content;
	i = 0;
	while (i < nbr_builtins)
	{
		if (ft_strcmp(cmd->cmd, builtins[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
