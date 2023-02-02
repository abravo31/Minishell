/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [11]pid_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:20:24 by motero            #+#    #+#             */
/*   Updated: 2023/01/31 21:02:17 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* Creation of a linked link that stores the pid of the process
** If first node, it add it tot eh garbage collector
** Otherwise it adds to the back of the list
*/
void	add_pid_to_list(t_minishell *msh, pid_t pid)
{
	t_list	*new;

	if (msh->pid == NULL)
	{
		new = allocate_and_store_node(pid);
		if (!new)
			error_safe_exit("LIST ERROR\n");
		msh->pid = new;
		add_to_garbage_collector((void *)&msh->pid, LST);
	}
	else
	{
		new = allocate_and_store_node(pid);
		if (!new)
			error_safe_exit("LIST ERROR\n");
		ft_lstadd_back(&msh->pid, new);
	}
}
