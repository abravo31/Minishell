/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:38:23 by motero            #+#    #+#             */
/*   Updated: 2023/02/11 16:01:48 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_status = 0;

void	minishell_loop(t_minishell *msh, int *tmp_fd_0, int *tmp_fd_1)
{
	int		i;

	i = 0;
	while (msh->status)
	{
		setup_loop(msh, tmp_fd_0, tmp_fd_1, &i);
		if (msh->prompt == NULL)
			break ;
		add_to_garbage_collector((void *)msh->prompt, INT);
		if (msh->prompt != NULL)
		{
			if (msh->prompt[0] != '\0')
				add_history(msh->prompt);
			if (!get_cmd(msh))
			{
				error_messages_default_cases(msh->parsing_error, 99);
				reset_and_free(msh);
				continue ;
			}
			ft_start_prompt(msh, *tmp_fd_0, *tmp_fd_1, &i);
		}
		reset_and_free(msh);
	}
}

int	launch_normal(char **envp)
{
	t_minishell	msh;
	int			tmp_fd[2];

	init_minishell(&msh);
	get_env(envp, &msh);
	minishell_loop(&msh, &tmp_fd[0], &tmp_fd[1]);
	if (msh.prompt)
		free(msh.prompt);
	free_garbage_collector(ALL);
	rl_clear_history();
	close(tmp_fd[0]);
	close(tmp_fd[1]);
	printf("exit\n");
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	launch_normal(env);
	return (0);
}

// int	launch_minishell(char *cmd, char **envp)
// {
// 	t_minishell	msh;
// 	int			i;
// 	t_list		*head;
// 	int			tmp_fd[2];

// 	init_minishell(&msh);
// 	get_env(envp, &msh);
// 	tmp_fd[0] = dup(STDIN_FILENO);
// 	tmp_fd[1] = dup(STDOUT_FILENO);
// 	add_to_garbage_collector((void *)&tmp_fd[0], FD);
// 	add_to_garbage_collector((void *)&tmp_fd[1], FD);
// 	list_env_to_char_env(&msh);
// 	i = 0;
// 	msh.fd_dup[0] = tmp_fd[0];
// 	msh.fd_dup[1] = tmp_fd[1];
// 	setup_signal_handlers();
// 	msh.prompt = cmd;
// 	if (msh.prompt == NULL)
// 		return (0);
// 	add_history(msh.prompt);
// 	//add_to_garbage_collector((void *)msh.prompt, INT);
// 	if (msh.prompt != NULL)
// 	{
// 		if (!get_cmd(&msh))
// 		{
// 			errors_messages_cases(msh.parsing_error, 99);
// 			reset_and_free(&msh);
// 			return (0);
// 		}
// 		head = msh.cmd_expand;
// 		msh.root = pipe_sequence(&msh.cmd_expand, &i);
// 		if (!msh.root)
// 			free_garbage_collector(ALL);
// 		add_to_garbage_collector((void *)msh.root, AST);
// 		msh.cmd_expand = head;
// 		//ft_printf("\nAST:\n");
// 		//print2DUtil(msh.root, 0);
// 		i = 0;
// 		if (singleton_heredoc(0) == 0 && msh.root)
// 			main_execution(&msh, msh.root, &i);
// 		dup2(tmp_fd[0], STDIN_FILENO);
// 		dup2(tmp_fd[1], STDOUT_FILENO);
// 		wait_for_children(&msh);
// 		if (msh.parsing_error)
// 			errors_messages_cases(msh.parsing_error, 99);
// 		reset_and_free(&msh);
// 	}
// 	// if (msh.prompt)
// 	// 	free(msh.prompt);
// 	free_garbage_collector(ALL);
// 	close(tmp_fd[0]);
// 	close(tmp_fd[1]);
// 	// printf("exit\n");
// 	return (0);
// }

// int	main(int argc, char **argv, char **env)
// {
// 	char	**cmds;
// 	int		i;

// 	i = 0;
// 	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
// 	{
// 		cmds = ft_split(argv[2], ';');
// 		while (cmds[i])
// 			launch_minishell(cmds[i++], env);
// 		free_double_pointer((void **)cmds);
// 	}
// 	else
// 		launch_normal(argc, argv, env);
// 	exit(g_status);
// }
