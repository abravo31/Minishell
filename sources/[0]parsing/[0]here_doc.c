/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:27:49 by motero            #+#    #+#             */
/*   Updated: 2023/02/10 21:46:46 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* function that will handle the heredoc redirection
** It will create a temporary file with the help of the delimeter
** and the index i and with the help of the readline function we will
** capture the input and write it inthe tmp file
** then we will return the name of the tmp file as a cmd_name node
** !! IMPORTANT!! this will probably crash if delimiter is "" during
**  the ft_srlen, test this again after expansion has been implemented
*/
void	here_doc(t_cmd *cmd, int *i)
{
	char		*delimiter;
	char		*line;
	int			tmp;
	char		*tmp_name;

	tmp_name = heredoc_init(cmd, i, &delimiter, &tmp);
	add_to_garbage_collector((void *)&tmp, FD);
	if (singleton_heredoc(0) >= 1 || !tmp_name)
		return (free(tmp_name), free(delimiter));
	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(0);
	while (line != NULL && ft_strncmp(line, delimiter, ft_strlen(delimiter))
		&& singleton_heredoc(0) == 0)
	{
		write(tmp, line, ft_strlen(line));
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
	}
	if (line == NULL && singleton_heredoc(0) == 0)
		ft_putstr_fd("\n", 1);
	terminate_heredoc(line, tmp_name, cmd, delimiter);
	close(tmp);
}

void	terminate_heredoc(char *line, char *tmp_name, t_cmd *cmd,
			char *delimiter)
{
	unlink_heredoc(tmp_name, cmd);
	free(line);
	free((void *)tmp_name);
	free(delimiter);
}

void	unlink_heredoc(char *tmp_name, t_cmd *cmd)
{
	if (singleton_heredoc(0) == 1)
		unlink(tmp_name);
	else
	{
		free(cmd->cmd);
		cmd->cmd = ft_strdup(tmp_name);
		if (!cmd->cmd)
			return (error_message("Malloc failed\n", 1));
	}
	get_next_line(-1);
}

int	singleton_heredoc(int i)
{
	static int	heredoc = 0;

	if (i < 0)
		heredoc = 0;
	else if (i > 0)
		heredoc = heredoc + i;
	return (heredoc);
}

/* Init the delimeter with \n, and the tmp file with .tmp
** as well as tmp index with itoa and free it
*/
char	*heredoc_init(t_cmd *cmd, int *i, char **delimiter, int *tmp)
{
	char		*tmp_name;
	char		*nbr_tmp;
	static int	index = 0;

	(void)*i;	
	nbr_tmp = ft_itoa(index);
	if (!nbr_tmp)
		return (error_safe_exit("Malloc failed", 1), NULL);
	tmp_name = ft_strjoin("/tmp/.tmp", nbr_tmp);
	free(nbr_tmp);
	if (!tmp_name)
		return (NULL);
	*delimiter = ft_strjoin(cmd->cmd, "\n");
	if (!*delimiter)
		return (free(tmp_name), NULL);
	*tmp = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*tmp == -1)
		return (free(tmp_name), free(*delimiter), NULL);
	index++;
	heredoc_signal_handlers();
	return (tmp_name);
}
