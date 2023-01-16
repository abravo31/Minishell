/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:38:23 by motero            #+#    #+#             */
/*   Updated: 2023/01/14 21:46:22 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>


void	free_cmd(void *content);
void	free_list(t_list *lst, void (*free_content)(void *));

int	main(int argc, char **argv, char **envp)
{
	t_list	*cmd;
	t_list	*head;
	char	*line;
	t_ast	*ast_root;
	int		i = 0;

	setup_signal_handlers();
	(void)argc;
	(void)argv;
	(void)envp;
	line = readline("PROMPT_NAME > cat << EOF > file | wc -c | tr -d " " > file2");
	(void)line;
	cmd = hardcode_cmds();
	head = cmd;
	print_cmd(cmd);
	ast_root = pipe_sequence(&cmd, &i);
	printf("\n");
	print2DUtil(ast_root, 0);
	free_ast(ast_root);
	free_list(head, &free_cmd);
	rl_clear_history();
	free(line);
	
}

void	free_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	free(cmd);
}

void	free_list(t_list *lst, void (*free_content)(void *))
{
	t_list	*current;

	while (lst)
	{
		current = lst;
		lst = lst->next;
		if (free_content)
			free_content((t_cmd *)current->content);
		free(current);
	}
}