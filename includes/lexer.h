/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/02/08 23:06:17 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structures.h"
# include "libft.h"
# include "garbage_collector.h"
# include "expander.h"

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

/*############################################################################*/
/*                              LEXER  FUNCTIONS						  */
/*############################################################################*/

void	delimitor(char **cmd, t_minishell *msh, int space);
int		is_token(char c);
t_token	eval_token(char *cmd);
t_cmd	*new_cmd(char *cmd, t_token id, int space);
char	*syntax_error(char where);
int		handle_first_node_error(t_minishell *msh);
void	check_parsing_errors(t_minishell *msh, int end);
int		end_quote(int d_quo, int s_quo);
int		is_quote(t_minishell *msh, int pos, char **cmd, int space);
void	iter_prompt(t_minishell *msh, char **str, int i);
void	__debug_parsing(t_list *cmd);

/*############################################################################*/
/*                              LEXER UTILITY FUNCTIONS						  */
/*############################################################################*/
int		get_cmd(t_minishell *msh);
void	get_char(char c, char **cmd);
int		is_identical(char *s1, char *s2);
void	reset_and_free(t_minishell *msh);
char	*ft_strjoin_cmd(char *s1, char *s2);
int		is_space(char c);

/*############################################################################*/
/*                              LINKED LIST FT                                */
/*############################################################################*/
// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// t_list	*ft_lstlast(t_list *lst);
// void	ft_lstiter(t_list *lst, void (*f)(void *));
// void	ft_lstclear(t_list **lst, void (*del)(void*));
// void	ft_lstdelone(t_list *lst, void (*del)(void*));
// void	ft_lstadd_front(t_list **lst, t_list *new);
// void	ft_lstadd_back(t_list **lst, t_list *new);
// int		ft_lstsize(t_list *lst);
// t_list	*ft_lstnew(void *content);

/*############################################################################*/
/*                              LIBFT FT TO BE ERASED					      */
/*############################################################################*/

char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);

#endif
