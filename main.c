/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:56:30 by abravo            #+#    #+#             */
/*   Updated: 2023/01/04 15:43:15 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_minishell(t_minishell *msh)
{   
    msh->status = 1;
    msh->prompt = NULL;
    msh->parsing_error = NULL;
}

void    clean_exit(t_minishell *msh)
{
    /* data */    
}

int main(int argc, char **argv, char **envp)
{
    t_minishell msh;
    
    init_minishell(&msh);
    while (msh.status)
    {
        msh.prompt = readline(PROMPT_NAME);
        if (get_str(&msh))
            printf("My line is: %s\n", msh.prompt);
        else
        {
            printf("parsing erros here\n");
        }
    }
    clean_exit(&msh);
    return (0);
}