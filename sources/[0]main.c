/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:38:23 by motero            #+#    #+#             */
/*   Updated: 2023/01/12 00:15:55 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

t_list	*ft_lstnew2(void const *content, size_t content_size)
{
	t_list	*new_node;

	if (!(new_node = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content)
	{
		if (!(new_node->content = malloc(content_size)))
		{
			free(new_node);
			return (NULL);
		}
		ft_memcpy(new_node->content, content, content_size);
		new_node->content_size = content_size;
	}
	else
	{
		new_node->content = NULL;
		new_node->content_size = 0;
	}
	new_node->next = NULL;
	return (new_node);
}

//cmd ahardcoded cat << EOF > file | wc -c | tr -d " " > file2
t_list	*hardcode_cmds(void)
{
	t_list	*head = NULL;
	t_list	*current = NULL;
	t_cmd	cmd;

	cmd.cmd = "cat";
	cmd.id = UNASSIGNED;
	current = ft_lstnew2(&cmd, sizeof(t_cmd));
	head = current;
	cmd.cmd = "<<";
	cmd.id = L_DREDIR;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "EOF";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = ">";
	cmd.id = R_REDIR;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "file";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "|";
	cmd.id = PIPE;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "wc";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "-c";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "|";
	cmd.id = PIPE;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "tr";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "-d";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = " ";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = ">";
	cmd.id = R_REDIR;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "file2";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	return (head);
}

//print whole cmd linked list with all the tokens
void	print_cmd(t_list *head)
{
	t_list	*current = head;
	t_cmd	*cmd;
	char	*id[]={"UNASSIGNED", "R_REDIR", "R_DREDIR","L_REDIR","L_DREDIR","PIPE","BUILTIN","D_QUOTE","S_QUOTE","CMD_NAME","CMD_WORD"};

	while (current)
	{
		cmd = (t_cmd *)current->content;
		printf("cmd: %s, id: %s\n", cmd->cmd, id[cmd->id]);
		current = current->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*cmd;
	char	*line;
	t_ast	*ast_root;

	setup_signal_handlers();
	(void)argc;
	(void)argv;
	(void)envp;
	line = readline("PROMPT_NAME > cat << EOF > file | wc -c | tr -d " " > file2");
	cmd = hardcode_cmds();
	print_cmd(cmd);
	ast_root = t_cmd_list_to_ast(cmd, 0);
	printf("\n\n");
	print_ast(ast_root, 0);
}
