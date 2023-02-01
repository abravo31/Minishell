/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:38:23 by motero            #+#    #+#             */
/*   Updated: 2023/02/02 00:18:46 by abravo           ###   ########.fr       */
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
	msh->env = NULL;
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
	printf("\n=======\nCLEAN EXIT\n=======\n");
	printf("propmt before freeing it's memory: %s\n", msh->prompt);
	free(msh->prompt);
}

t_env	*new_env(char *key, char *value)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env)); //IMPORTANT check malloc failed
	elem->key = key;
	elem->value = value;
	return (elem);
}

char	*str_from_range(char *env, int start, int end)
{
	char	*str;
	int		i;

	i = 0;
	if (!(str = malloc(sizeof(char) * end - start)))
		return NULL;
	while (start + i < end)
	{
		str[i] = env[start + i];
		i++;
	}
	return (str);
}

void	get_env(char **env, t_minishell *msh)
{
	int	i;
	int	j;
	int k;
	char	*key;
	char	*value;

	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		if (!(key = str_from_range(env[i], 0, j)))//malloc(sizeof(char *) * j)))
			return ;
		k = 0;
		while (env[i][j + k])
			k++;
		if (!(value = str_from_range(env[i], j, k)))//malloc(sizeof(char *) * (j + 1))))
			return ;
		ft_lstadd_back(&msh->env, ft_lstnew((void *)new_env(key, value)));
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	msh;
	int			i;
	t_list		*head;

	i = 0;
	(void)argc;
	(void)argv;
	
	init_minishell(&msh);
	get_env(envp, &msh);
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
