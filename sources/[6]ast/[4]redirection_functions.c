/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [4]redirection_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:56:22 by motero            #+#    #+#             */
/*   Updated: 2023/01/27 18:30:09 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
This function initializes an array of function pointers with the address of the 
corresponding redirection functions, which are redirection_right, 
redirection_double_right, redirection_left, and redirection_double_left.
The array is indexed by the id of the redirection operator, allowing for easy
lookup and execution of the correct redirection function.
*/
void	init_redirection_function(t_ast *(*redirection_function[4])
(t_list **, int *))
{
	redirection_function[0] = &redirection_right;
	redirection_function[1] = &redirection_double_right;
	redirection_function[2] = &redirection_left;
	redirection_function[3] = &redirection_double_left;
}

/*
Creates a redirection AST node with a cmd_redir node as the left 
child and a cmd_name node as the right child.
*/
t_ast	*redirection_left(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	left = NULL;
	right = NULL;
	left = cmd_redir(head, i);
	right = cmd_name(head, i);
	return (create_ast_no_terminal(REDIRECTION, left, right));
}

/*
Creates a redirection AST node with a cmd_redir node as 
the left child and a cmd_name node as the right child.
*/
t_ast	*redirection_right(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	left = NULL;
	right = NULL;
	left = cmd_redir(head, i);
	right = cmd_name(head, i);
	return (create_ast_no_terminal(REDIRECTION, left, right));
}

/*
Creates a redirection AST node with a cmd_redir node as the 
left child and a cmd_name node as the right child.
*/
t_ast	*redirection_double_left(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	left = NULL;
	right = NULL;
	left = cmd_redir(head, i);
	here_doc((t_cmd *)(*head)->content, i);
	right = cmd_name(head, i);
	return (create_ast_no_terminal(REDIRECTION, left, right));
}

/*function that will handle the heredoc redirection
** It will create a temporary file with the help of the delimeter and the index i
** and with the help of the readline function we will capture the input and write it inthe tmp file
** then we will return the name of the tmp file as a cmd_name node
*/
void	here_doc(t_cmd *cmd, int *i)
{
	char		*delimiter;
	char		*line;
	int			tmp;
	char const	*tmp_name = ft_strjoin("tmp", ft_itoa(*i));

	if (!tmp_name)
		return ;
	delimiter = cmd->cmd;
	printf("delimiter : %s\n", delimiter);
	tmp = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp == -1)
		return ;
	line = readline("heredoc> ");
	while (line != NULL && ft_strncmp(line, delimiter, ft_strlen(line) - 1))
	{
		write(tmp, line, ft_strlen(line));
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	free((void *)tmp_name);
	close(tmp);
}	

/*
Creates a redirection AST node with a cmd_redir node as 
the left child and a cmd_name node as the right child.
*/
t_ast	*redirection_double_right(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	left = NULL;
	right = NULL;
	left = cmd_redir(head, i);
	right = cmd_name(head, i);
	return (create_ast_no_terminal(REDIRECTION, left, right));
}
