/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [0]here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:27:49 by motero            #+#    #+#             */
/*   Updated: 2023/01/28 18:21:05 by motero           ###   ########.fr       */
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
	char const	*tmp_name = ft_strjoin(".tmp", ft_itoa(*i));

	if (!tmp_name || singleton_heredoc(0) >= 1)
		return ;
	delimiter = ft_strjoin(cmd->cmd, "\n");
	tmp = open(tmp_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp == -1)
		return ;
	heredoc_signal_handlers();
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
	if (singleton_heredoc(0) == 1)
		unlink(tmp_name);
	else
		cmd->cmd = ft_strdup(tmp_name);
	free(line);
	get_next_line(-1);
	free((void *)tmp_name);
	free(delimiter);
	close(tmp);
}

int	singleton_heredoc(int i)
{
	static int	heredoc = 0;

	heredoc = heredoc + i;
	return (heredoc);
}
