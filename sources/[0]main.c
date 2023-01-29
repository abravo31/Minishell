/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:38:23 by motero            #+#    #+#             */
/*   Updated: 2023/01/29 20:41:45 by motero           ###   ########.fr       */
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

void	free_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	free(cmd->cmd);
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
	//msh->cmd = NULL;
	printf("\nreset_and_free\n");
	print_cmd(msh->cmd);
	ft_lstclear(&msh->cmd, &free_cmd);
	msh->parsing_error = NULL;
	//free(msh->prompt);
	ft_lstclear(&msh->fd, &free);
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
			ft_expansion(&msh);
			msh.root = pipe_sequence(&msh.cmd, &i);
			msh.cmd = head;
			//print_cmd(msh.cmd);
			ft_printf("\nAST:\n");
			print2DUtil(msh.root, 0);
			if (singleton_heredoc(0) == 0)
				main_execution(&msh, msh.root);
			free_ast(msh.root);
			if (msh.parsing_error)
				printf("%s\n", msh.parsing_error);
		}
		reset_and_free(&msh);
	}
	printf("exit\n");
	clean_exit(&msh);
	return (0);
}
