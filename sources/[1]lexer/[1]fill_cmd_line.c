/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]fill_cmd_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:25:18 by abravo            #+#    #+#             */
/*   Updated: 2023/01/28 20:09:04 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*temp;

// 	if (!new)
// 		return ;
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	temp = ft_lstlast(*lst);
// 	temp->next = new;
// }

// void	ft_lstadd_front(t_list **lst, t_list *new)
// {
// 	new->next = *lst;
// 	*lst = new;
// }

// void	ft_lstdelone(t_list *lst, void (*del)(void*))
// {
// 	if (!lst || !del)
// 		return ;
// 	(del)(lst->content);
// 	free(lst);
// }

// int	ft_lstsize(t_list *lst)
// {
// 	size_t	i;

// 	i = 0;
// 	while (lst != NULL)
// 	{
// 		lst = lst->next;
// 		i++;
// 	}
// 	return (i);
// }

// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*new;

// 	new = malloc(sizeof(t_list));
// 	if (!new)
// 		return (0);
// 	new->content = content;
// 	new->next = NULL;
// 	return (new);
// }

// void	ft_lstclear(t_list **lst, void (*del)(void*))
// {
// 	t_list	*temp;

// 	printf("lstclear\n");
// 	while (*lst)
// 	{
// 		printf("lst content: %d", *(int *)(*lst)->content);
// 		temp = (*lst)->next;
// 		ft_lstdelone(*lst, del);
// 		*lst = temp;
// 	}
// 	*lst = NULL;
// }

// void	ft_lstiter(t_list *lst, void (*f)(void *))
// {
// 	if (!lst)
// 		return ;
// 	while (lst)
// 	{
// 		(f)(lst->content);
// 		lst = lst->next;
// 	}
// }

// t_list	*ft_lstlast(t_list *lst)
// {
// 	t_list	*temp;

// 	temp = lst;
// 	if (!temp)
// 		return (temp);
// 	while (temp->next)
// 	{
// 		temp = temp->next;
// 	}
// 	return (temp);
// }

// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_list	*new;
// 	t_list	*first;

// 	first = 0;
// 	while (lst)
// 	{
// 		new = ft_lstnew(f(lst->content));
// 		if (!new)
// 		{
// 			ft_lstclear(&first, del);
// 			return (0);
// 		}
// 		ft_lstadd_back(&first, new);
// 		lst = lst->next;
// 	}
// 	return (first);
// }

