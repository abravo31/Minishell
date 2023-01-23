/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:56:30 by abravo            #+#    #+#             */
/*   Updated: 2023/01/04 21:51:40 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_minishell(t_minishell *msh)
{   
    msh->status = 1;
    msh->prompt = NULL;
    msh->parsing_error = NULL;
    msh->cmd = NULL;
}

void    reset_and_free(t_minishell *msh)
{
    msh->cmd = NULL;
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
        if (get_cmd(&msh))
            printf("My line is: %s\n", msh.prompt);
        if (msh.parsing_error)
            printf("%s\n", msh.parsing_error);
    	reset_and_free(&msh);
    }
    clean_exit(&msh);
    return (0);
}
