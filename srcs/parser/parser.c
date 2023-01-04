/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:25:42 by abravo            #+#    #+#             */
/*   Updated: 2023/01/04 16:25:45 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int get_str(t_minishell *msh)
{
    int i;
    char    *str;

    i = 0;
    str = NULL;
    while (msh->prompt[i] && msh->prompt[i] != '>')
    {
        get_char(msh->prompt[i], &str);
        i++;
    }
    printf("str id %s\n", str);
    return(1);
}