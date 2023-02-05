/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]no_terminal_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:13:22 by motero            #+#    #+#             */
/*   Updated: 2023/02/04 20:29:39 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
**-An Abstract Syntax Tree (AST) is a data structure used to represent the
**structure of a program's source code. It is commonly used in compilers and 
**interpreters to simplify and speed up the process of analyzing and
**interpreting source code.
**
**A grammar-free table is a table that describes the structure of the
** grammar for a programming language, but does not specify the exact syntax.
**It is used as a guide for constructing an AST.
**
**To build an AST, the source code is first tokenized into a list of tokens.
**The tokens are then parsed according to the grammar-free table to create a
**tree-like structure that represents the structure of the code. The tree is
**built recursively, starting with the root node and expanding to include child
**nodes for each element in the source code.
**
**The table below describes the structure of the grammar for a shell-like
** language 
** The left-hand side of the table shows the non-terminal symbols,
**& the right-hand side shows the possible expansions of each symbol.
**The symbols on the right-hand side can be either terminal symbols
**(such as "WORD" and "<") or non-terminal symbols
**(such as "cmd_name" and "pipe_sequence").
**
**During the parsing process, the parser traverses the input stream of tokens
**according to the grammar-free table, creating nodes in the AST for each
**non-terminal symbol encountered. The process is recursive, meaning that the
**parser will continue to expand the tree by recursively calling the appropriate
**production rule for each non-terminal symbol until reaches the end of
**the input stream.
**
**In our implementation, the functions like pipe_sequence, complexe_command, 
**simple_command, argument, redirection, and init_redirection_function are used
**to build the AST according to the grammar-free table. The functions take the
**token list and the current position in the list as input, and return an
** AST node representing the corresponding non-terminal symbol.
**
**the following are the no-terminalf functions of are grammar table
**pipe_sequence 	:complexe_command
**				| complexe_command '|' pipe_sequence
**				;
**complexe_command : redirection complexe_command
**				 | simple_command 
**				 | redirection simple_command 
**				 ;
**simple_command	: cmd_name
**				| cmd_name argument
**				;
**argument		: cmd_word
**				| cmd_word cmd_word
**                ;
**redirection 	: '<' cmd_word
**				|  cmd_word '>' 
**				| '<<' cmd_word
**				|  cmd_word '>>' 
**				;                 
***/

/*
pipe_sequence - function that creates an AST node for a pipe sequence.
A pipe sequence is a series of one or more complex commands separated 
by the pipe operator '|'.
This function takes a pointer to a linked list of tokens and an index.
It starts by creating a left AST node with the first complex command.
Then it loops through the linked list while the current token is '|' operator.
For each iteration, it moves to the next token and creates a right AST node 
with the next pipe sequence.
If there are no more pipe operators, the right AST node is set to NULL.
Finally, it returns an AST node with the type PIPE_SEQUENCE and left 
and right children set to the left and right AST nodes.
*/
t_ast	*pipe_sequence(t_list **head, int *i)
{
	t_ast			*left;
	t_ast			*right;
	static int		pipe_count = 0;

	if (!head || !(*head))
		return (NULL);
	if (*i == 0)
		pipe_count = 0;
	pipe_count++;
	left = complexe_command(head, i);
	right = NULL;
	while ((*head) && ((t_cmd *)(*head)->content)->id == PIPE)
	{
		*head = (*head)->next;
		(*i)++;
		right = pipe_sequence(head, i);
	}
	if (left == NULL && right == NULL)
		return (NULL);
	if (right == NULL && pipe_count == 1 && (left->id->op == CMPLX_BUILT
			|| left->id->op == SIMPLE_BUILTIN))
		return (left);
	return (create_ast_no_terminal(PIPE_SEQUENCE, left, right));
}

/*
complexe_comand function following this new rule
complexe_command : complexe_command redirection
				 | simple_command 
				 | simple_command redirection
				 ;

This function is for parsing the complex command in the input command line.
It starts by initializing the left and right pointers of the AST as NULL.
Then, it checks if there are any redirection operators at the beginning of 
the input command line.
If there are, it assigns the left pointer to the first redirection operator
and recursively calls the function to find any additional redirection 
operators before the command.
Once it finds the command, it assigns the left pointer to the command and 
recursively calls the function to find any additional redirection operators
after the command.
If there are no more elements in the input command line, the function will
return the left pointer as the final AST node for the complex command.
Otherwise, it creates a new AST node for the complex command and assigns
the left and right pointers as its left and right children.
*/

t_ast	*complexe_command(t_list **head, int *i)
{
	t_ast	*left;
	t_ast	*right;

	if ((*head) == NULL)
		return (NULL);
	left = NULL;
	right = NULL;
	if ((*head) && is_redirection((t_cmd *)(*head)->content))
	{
		left = redirection(head, i);
		right = complexe_command(head, i);
	}
	if ((*head) && ((t_cmd *)(*head)->content)->id == WORD)
	{
		right = simple_command(head, i);
		left = complexe_command(head, i);
	}
	if (right == NULL)
		return (left);
	if (left == NULL)
		return (right);
	if (left->id->op == SIMPLE_BUILTIN || right->id->op == SIMPLE_BUILTIN
		|| left->id->op == CMPLX_BUILT || right->id->op == CMPLX_BUILT)
		return (create_ast_no_terminal(CMPLX_BUILT, left, right));
	return (create_ast_no_terminal(COMPLEXE_COMMAND, left, right));
}

/*
This function is responsible for creating an AST node for 
a simple command. It does so by:

-Checking if the current command is of type UNASSIGNED.
-If it is, it gets the command name and assigns it to the left child 
the AST node.
-If the new node is also of type UNASSIGNED, we deduce it is an argument 
and assigns it to the right child of the AST node.
-Finally, it returns the AST node representing this simple command.
*/
t_ast	*simple_command(t_list **head, int *i)
{
	t_ast			*left;
	t_ast			*right;

	if ((*head) == NULL)
		return (NULL);
	left = NULL;
	right = NULL;
	if (((t_cmd *)(*head)->content)->id == WORD)
	{
		left = cmd_name(head, i);
		if ((*head) && ((t_cmd *)(*head)->content)->id == WORD)
			right = argument(head, i, left);
	}
	if (!left && !right)
		return (NULL);
	if (left->id->token == BUILTIN)
		return (create_ast_no_terminal(SIMPLE_BUILTIN, left, right));
	return (create_ast_no_terminal(SIMPLE_COMMAND, left, right));
}

/*
This function checks if the current command is an argument and creates 
an AST node for it. It also handles the case where there are multiple arguments.

-The head of the command list is checked for NULL. 
If it is, the function returns NULL.
-A variable cmd is assigned the current command.
-The left and right nodes of the AST are set to NULL.
-If the current command is an argument, the left node is set to the
cmd_word and the right node is set to NULL.
-The AST node is created with the type ARGUMENT and left and right
nodes as arguments. The function then returns this node.
*/
t_ast	*argument(t_list **head, int *i, t_ast *command)
{
	t_ast			*left;
	t_ast			*right;
	t_cmd			*cmd;

	if ((*head) == NULL)
		return (NULL);
	cmd = (t_cmd *)(*head)->content;
	left = NULL;
	if (cmd->id == WORD)
		left = cmd_arg(head, i, command);
	right = NULL;
	if (left == NULL)
		return (NULL);
	return (create_ast_no_terminal(ARGUMENT, left, right));
}
//left = cmd_word(head, i);

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
