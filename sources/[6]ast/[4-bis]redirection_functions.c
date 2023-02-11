/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [4-bis]redirection_functions.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 21:56:22 by motero            #+#    #+#             */
/*   Updated: 2023/02/11 01:38:13 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
 This function is used to extract the command name from the input list 
 and create an AST node for it.
*/
t_ast	*cmd_filename(t_list **head, int *i)
{
	t_cmd	*cmd;

	if ((*head) == NULL)
		return (NULL);
	cmd = (t_cmd *)(*head)->content;
	if (cmd->id == WORD)
	{
		cmd->id = FILENAME;
		(*i)++;
		(*head) = (*head)->next;
		return (create_ast_terminal(cmd, NULL, NULL));
	}
	return (NULL);
}

/*
The function redirection is responsible for handling different
types of redirection operators.

-It checks the type of redirection operator currently at the head
of the list and calls the appropriate function to handle it.
-It uses an array of function pointers, redirection_function,
to store the functions for handling each type of redirection.
-This array is initialized with the init_redirection_function function,
which assigns the appropriate functions to each index of the array.
-The redirection_function array is then used to call the function that
corresponds to the current redirection operator.
-It iterates over the possible redirection operators, and when it finds
the one matching the current operator it calls the function with the
function pointer of that operator.
*/
t_ast	*redirection(t_list **head, int *i)
{
	int			index;
	t_ast		*(*redirection_function[4])(t_list **, int *i);

	if ((*head) == NULL)
		return (NULL);
	init_redirection_function(redirection_function);
	index = 1;
	while (index <= L_DREDIR)
	{
		if (index == (int)((t_cmd *)(*head)->content)->id)
			return (redirection_function[index - 1](head, i));
		index++;
	}
	return (NULL);
}
