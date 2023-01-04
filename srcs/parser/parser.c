#include "../../minishell.h"

// Function that returns 1 or 0 weither c is a token or not
int     is_token(char c)
{
    size_t  i;
    static const char *tokens[] = {
        ">",
        "<",
        "|",
    };
    i = 0;
    while (tokens[i])
    {
        if (tokens[i][0] == c)
            return (1);
        i++;
    }
    return (0);
}

// Function to check if string is a builtin
int     is_builtin(char *cmd)
{
    return (0);
}

// Function to return corresponding token from string
t_token eval_token(char *cmd)
{
    if (is_identical(">", cmd))
        return (R_REDIR);
    else if (is_identical(">>", cmd))
        return (R_DREDIR);
    else if (is_identical("<", cmd))
        return (L_REDIR);
    else if (is_identical("<<", cmd))
        return (L_DREDIR);
    else if (is_identical("|", cmd))
        return (PIPE);
    else if (is_builtin(cmd))
        return (BULTINS);
    return (UNASSIGNED);
}

t_cmd   *new_cmd(char   *cmd, t_token id)
{
    t_cmd   *elem;

    elem = malloc(sizeof(t_cmd)); //IMPORTANT check malloc failed
    elem->cmd = cmd;
    elem->id = id;
    return (elem);
}

void	check_parsing_errors(t_minishell *msh)
{
	t_list *iter = msh->cmd;
    t_cmd   *current = NULL;
    while (iter)
    {
        current = (t_cmd*) iter->content;
		if (is_token(current->cmd[0]) && !current->id)
		{
			msh->parsing_error = ft_strdup("syntax error near unexpected token \'?\'");
			msh->parsing_error[ft_strlen(msh->parsing_error) - 2] = current->cmd[0];
			break ;
		}
        iter = iter->next;
    }
}

// Function to handle space delimitor case
// will create and pus a new node with cmd and it's token
void    delimitor(char **cmd, t_minishell *msh)
{
    if (!*cmd || msh->parsing_error)
        return ;
    ft_lstadd_back(&msh->cmd, ft_lstnew((void *)new_cmd(*cmd, eval_token(*cmd))));
	check_parsing_errors(msh);
    *cmd = NULL;
}

void __debug_parsing(t_minishell *msh)
{
    t_list *iter = msh->cmd;
    t_cmd   *current = NULL;
    while (iter)
    {
        current = (t_cmd*) iter->content;
        printf("{%d}[%s]\n", current->id, current->cmd);
        iter = iter->next;
    }
}

// Function to parse cmd from user input
int get_cmd(t_minishell *msh)
{
    int i;
    char    *str;

    i = 0;
    str = NULL;
    while (msh->prompt[i] && !msh->parsing_error)
    {
        if (msh->prompt[i] == ' ')
            delimitor(&str, msh);
		if ((is_token(msh->prompt[i]) && str && !is_token(str[0]))
		|| (!is_token(msh->prompt[i]) && str && is_token(str[0])))
			delimitor(&str, msh);
        get_char(msh->prompt[i], &str);
        i++;
    }
    delimitor(&str, msh);
    __debug_parsing(msh);
    return(!msh->parsing_error);
}
