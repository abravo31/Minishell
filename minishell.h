/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:51:54 by abravo            #+#    #+#             */
/*   Updated: 2023/01/04 21:44:18 by abravo           ###   ########.fr       */
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
    D_QUOTE,
    S_QUOTE,
} t_token;

typedef struct s_cmd
{
    char            *cmd;
    t_token         id;
} t_cmd;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_minishell
{
    char    *prompt;
    char    *parsing_error;
    int     status;
    t_list  *cmd;
    t_list  *env;
} t_minishell;

/* parser */
int     get_cmd(t_minishell *msh);
void    get_char(char c, char **cmd);
int     is_identical(char *s1, char *s2);
void    reset_and_free(t_minishell *msh);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int	    ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
#endif
