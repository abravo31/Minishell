/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_terminal functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:13:22 by motero            #+#    #+#             */
/*   Updated: 2023/01/13 22:20:17 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
the following are the no-terminalf functions of are grammar table
pipe_sequence    : complexe_command
				 | complexe_command '|' complexe_command
                 | complexe_command '|' pipe_sequence
                 ;
complexe_command : simple_command 
				 | simple_command  redirection
				 | redirection	simple_command
simple_command	: cmd_name
				| cmd_name argument
				;
argument		: cmd_word
				| cmd_word cmd_word
                 ;
redirection 	: '<' cmd_word
				| '>' cmd_word
				| '<<' cmd_word
				| '>>' cmd_word
				;                 
*/

size_t	ft_lstlen(t_list *lst)
{
    size_t len;

    len = 0;
    while (lst)
    {
        len++;
        lst = lst->next;
    }
    return (len);
}

t_ast	*pipe_sequence(t_list *head, int *i)
{
	t_ast			*left;
	t_ast			*right;
	t_cmd			*cmd;
	size_t const	list_len = ft_lstsize(head);

	if (head == NULL)
		return (NULL);
	left = complexe_command(head, i);
	right = NULL;
	while (*i < list_len && ((t_cmd *)head->content)->id == PIPE)
	{
		cmd = (t_cmd *)head->content;
		head = head->next;
		(*i)++;
		right = pipe_sequence(head, i);
	}
	if (*i < list_len - 1)
		return (left);
	return (create_ast_node(cmd, left, right));
}