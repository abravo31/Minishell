/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:36:43 by motero            #+#    #+#             */
/*   Updated: 2023/01/24 18:03:26 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structures.h"
# include "libft.h"
# include "garbage_collector.h"

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

void	delimitor(char **cmd, t_minishell *msh);
int		is_token(char c);
t_token	eval_token(char *cmd);
t_cmd	*new_cmd(char *cmd, t_token id);
char	*syntax_error(char where);
int		handle_first_node_error(t_minishell *msh);
void	check_parsing_errors(t_minishell *msh, int end);
int		end_quote(int d_quo, int s_quo);
int		is_quote(t_minishell *msh, int pos, char **cmd);
void	__debug_parsing(t_minishell *msh);

/*############################################################################*/
/*                              LEXER UTILITY FUNCTIONS						  */
/*############################################################################*/
int		get_cmd(t_minishell *msh);
void	get_char(char c, char **cmd);
int		is_identical(char *s1, char *s2);
void	reset_and_free(t_minishell *msh);

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
