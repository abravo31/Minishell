/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:51:54 by abravo            #+#    #+#             */
/*   Updated: 2023/01/04 16:26:35 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# define PROMPT_NAME "Minishell > "

typedef enum e_token
{
    UNASSIGNED,
    R_REDIR,
    R_DREDIR,
    L_REDIR,
    L_DREDIR,
    PIPE,
    BULTINS,
    CMD,
} t_token;

typedef struct s_minishell
{
    char    *prompt;
    char    *parsing_error;
    int     status;
} t_minishell;

typedef struct s_cmd
{
    char    *cmd;
    t_token id;
} t_cmd;

/* parser */
int     get_str(t_minishell *msh);
void    get_char(char c, char **cmd);

#endif