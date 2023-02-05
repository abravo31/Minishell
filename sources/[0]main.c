/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:38:23 by motero            #+#    #+#             */
/*   Updated: 2023/02/05 00:07:49 by motero           ###   ########.fr       */
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
	msh->fd_in = -2;
	msh->fd_out = -2;
	msh->pid = NULL;
	msh->env = NULL;
}

void	reset_and_free(t_minishell *msh)
{
	free_garbage_collector(EXCEPT_ENV);
	singleton_heredoc(-1);
	msh->parsing_error = NULL;
	msh->cmd = NULL;
	msh->root = NULL;
	msh->fd_in = -2;
	msh->fd_out = -2;
	msh->pid = NULL;
	msh->path = NULL;
}

void	clean_exit(t_minishell *msh)
{
	printf("\n=======\nCLEAN EXIT\n=======\n");
	printf("propmt before freeing it's memory: %s\n", msh->prompt);
	free(msh->prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	msh;
	int			i;
	t_list		*head;
	int			tmp_fd[2];

	(void)argc;
	(void)argv;
	init_minishell(&msh);
	get_env(envp, &msh);
	while (msh.status)
	{
		list_env_to_char_env(&msh);
		i = 0;
		tmp_fd[0] = dup(STDIN_FILENO);
		add_to_garbage_collector((void *)&tmp_fd[0], FD);
		tmp_fd[1] = dup(STDOUT_FILENO);
		add_to_garbage_collector((void *)&tmp_fd[1], FD);
		msh.fd_dup[0] = tmp_fd[0];
		msh.fd_dup[1] = tmp_fd[1];
		setup_signal_handlers();
		msh.prompt = readline(PROMPT_NAME);
		if (msh.prompt == NULL)
		{
			break ;
		}
		add_to_garbage_collector((void *)msh.prompt, INT);
		if (msh.prompt != NULL)
		{
			if (!get_cmd(&msh))
			{
				printf("%s\n", msh.parsing_error);
				reset_and_free(&msh);
				continue ;
			}
			head = msh.cmd;
			msh.root = pipe_sequence(&msh.cmd, &i);
			if (!msh.root)
				free_garbage_collector(EXCEPT_ENV);
			add_to_garbage_collector((void *)msh.root, AST);
			msh.cmd = head;
			//ft_printf("\nAST:\n");
			//print2DUtil(msh.root, 0);
			i = 0;
			if (singleton_heredoc(0) == 0 && msh.root)
				main_execution(&msh, msh.root, &i);
			wait_for_children(&msh);
			dup2(tmp_fd[0], STDIN_FILENO);
			dup2(tmp_fd[1], STDOUT_FILENO);
			if (msh.parsing_error)
				printf("%s\n", msh.parsing_error);
		}
		reset_and_free(&msh);
	}
	if (msh.prompt)
		free(msh.prompt);
	free_garbage_collector(ALL);
	printf("exit\n");
	// free(msh.prompt);
	clean_exit(&msh);
	return (0);
}
