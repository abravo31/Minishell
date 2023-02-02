/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:27:49 by motero            #+#    #+#             */
/*   Updated: 2023/02/02 17:39:12 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	if (singleton_heredoc(0) >= 1 || !tmp_name)
		return ;
	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(0);
	while (line != NULL && ft_strncmp(line, delimiter, ft_strlen(delimiter))
		&& singleton_heredoc(0) == 0)
	{
		printf("line: %s\n", line);
		write(tmp, line, ft_strlen(line));
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
	}
	if (singleton_heredoc(0) == 1)
		unlink(tmp_name);
	else
		cmd->cmd = ft_strdup(tmp_name);
	printf("before free gnl\n");
	get_next_line(-1);
	free(line);
	free((void *)tmp_name);
	free(delimiter);
	close(tmp);
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
	char	*tmp_name;
	char	*nbr_tmp;

	nbr_tmp = ft_itoa(*i);
	tmp_name = ft_strjoin(".tmp", nbr_tmp);
	free(nbr_tmp);
	if (!tmp_name)
		return (NULL);
	*delimiter = ft_strjoin(cmd->cmd, "\n");
	*tmp = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*tmp == -1)
		return (free(tmp_name), free(*delimiter), NULL);
	heredoc_signal_handlers();
	return (tmp_name);
}
