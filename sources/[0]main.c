/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:38:23 by motero            #+#    #+#             */
/*   Updated: 2023/01/30 16:49:25 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bash(void *content);
void	free_list(t_list *lst, void (*free_content)(void *));

// int	main(int argc, char **argv, char **envp)
// {
// 	t_list	*cmd;
// 	t_list	*head;
// 	char	*line;
// 	t_ast	*ast_root;
// 	int		i = 0;

// 	setup_signal_handlers();
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	line = readline("PROMPT_NAME > cat << EOF > file | wc -c | tr -d " " > file2");
// 	(void)line;
// 	cmd = hardcode_cmds();
// 	head = cmd;
// 	print_cmd(cmd);
// 	ast_root = pipe_sequence(&cmd, &i);
// 	printf("\n");
// 	print2DUtil(ast_root, 0);
// 	free_ast(ast_root);
// 	free_list(head, &free_cmd);
// 	rl_clear_history();
// 	free(line);
// }



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

void	init_minishell(t_minishell *msh)
{
	msh->status = 1;
	msh->prompt = NULL;
	msh->parsing_error = NULL;
	msh->cmd = NULL;
	msh->fd = NULL;
}


void	reset_and_free(t_minishell *msh)
{
	free_garbage_collector();
	//free_ast(msh->root);
	ft_lstclear(&msh->fd, &free);
	msh->parsing_error = NULL;
	msh->cmd = NULL;
}

void	clean_exit(t_minishell *msh)
{
	(void)msh;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	msh;
	int			i;
	t_list		*head;

	i = 0;
	(void)argc;
	(void)argv;
	(void)envp;
	init_minishell(&msh);
	while (msh.status)
	{
		setup_signal_handlers();
		msh.prompt = readline(PROMPT_NAME);
		if (msh.prompt == NULL)
		{
			break ;
		}
		if (msh.prompt != NULL)
		{
			if (get_cmd(&msh))
				printf("My line is: %s\n", msh.prompt);
			head = msh.cmd;
			msh.root = pipe_sequence(&msh.cmd, &i);
			if (!msh.root)
				free_garbage_collector();
			add_to_garbage_collector((void *)msh.root, AST);
			msh.cmd = head;
			ft_printf("\nAST:\n");
			print2DUtil(msh.root, 0);
			if (singleton_heredoc(0) == 0 && msh.root)
				main_execution(&msh, msh.root);
			if (msh.parsing_error)
				printf("%s\n", msh.parsing_error);
		}
		reset_and_free(&msh);
	}
	printf("exit\n");
	clean_exit(&msh);
	return (0);
}
