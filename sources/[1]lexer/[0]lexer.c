#include "lexer.h"

// Function to parse cmd from user input
int	get_cmd(t_minishell *msh)
{
	int		i;
	char	*str;	

	i = 0;
	str = NULL;
	while (msh->prompt[i] && !msh->parsing_error)
	{
		//__debug_parsing(msh);
		if (msh->prompt[i] == ' ')
			delimitor(&str, msh);
		else if (msh->prompt[i] != ' ' && (msh->prompt[i] != '\'' && msh->prompt[i] != '\"'))
		{
			 //printf("%c\n", msh->prompt[i]);
			if ((is_token(msh->prompt[i]) && str && !is_token(str[0]))
				|| (!is_token(msh->prompt[i]) && str && is_token(str[0])))
			{
				//printf("msh : %c\n prev : %c\n", msh->prompt[i], str[0]);
				delimitor(&str, msh);
			}
			if ((msh->prompt[i] == '>' || msh->prompt[i] == '<') && str && str[0] == '|')
			{
				//printf("str[0] : %c\n", str[0]);
				delimitor(&str, msh);
			}
			get_char(msh->prompt[i], &str);
			printf("%s\n", str);
		}
		else if (msh->prompt[i] == '\'' || msh->prompt[i] == '\"')
		{
			if (i > 0 && !is_token(msh->prompt[i - 1]) && msh->prompt[i - 1] != ' ')
				delimitor(&str, msh);
			i = is_quote(msh, i, &msh->prompt);
		}
		i++;
	}
	delimitor(&str, msh);
	//check_parsing_errors(msh, 0);
	__debug_parsing(msh);
	check_parsing_errors(msh, 1);
	return (!msh->parsing_error);
}

// Function to handle space delimitor case
// will create and pus a new node with cmd and it's token
void	delimitor(char **cmd, t_minishell *msh)
{
	t_list	*new;

	if (!*cmd || msh->parsing_error)
		return ;
	if (msh->cmd == NULL)
	{
		msh->cmd = ft_lstnew((void *)new_cmd(*cmd, eval_token(*cmd)));
		if (!msh->cmd)
			printf("error while adding a delimitor, but you forgot to free!\n");
		add_to_garbage_collector((void *)&msh->cmd, CMD);
	}
	else
	{
		new = ft_lstnew((void *)new_cmd(*cmd, eval_token(*cmd)));
		if (!new)
		{
			free_garbage_collector();
			printf("error while adding a delimitor, still not error or way toe xit this function!\n");
			return ;
		}
		ft_lstadd_back(&msh->cmd, new);
	}
	check_parsing_errors(msh, 0);
	*cmd = NULL;
}

// Function that returns 1 or 0 weither c is a token or not
int	is_token(char c)
{
	size_t				i;
	static const char	*tokens[] = {
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
int	is_builtin(char *cmd)
{
	(void) cmd;
	return (0);
}

// Function to return corresponding token from string
t_token	eval_token(char *cmd)
{
	if (cmd[0] == '\"')
		return (D_QUOTE);
	if (cmd[0] == '\'')
		return (S_QUOTE);
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
	else if (!is_token(cmd[0]))
		return (WORD);
	return (UNASSIGNED);
}

t_cmd	*new_cmd(char *cmd, t_token id)
{
	t_cmd	*elem;

	elem = malloc(sizeof(t_cmd)); //IMPORTANT check malloc failed
	elem->cmd = cmd;
	elem->id = id;
	return (elem);
}

//Function to display syntax error at character where.
char	*syntax_error(char where)
{
	char	*ret;

	if (where == '\n')
	{
		ret = ft_strdup("syntax error near unexpected token \'newline\'");
		if (!ret)
		{
			free_garbage_collector();
			printf("error while adding a delimitor, still not error or way toe xit this function!\n");
			exit(2);
		}
		add_to_garbage_collector((void *)&ret, INT);
		return (ret);
	}
	ret = ft_strdup("syntax error near unexpected token \'?\'");
	if (!ret)
	{
		free_garbage_collector();
		printf("error while adding a delimitor, still not error or way toe xit this function!\n");
		exit(2);
	}
	ret[ft_strlen(ret) - 2] = where;
	add_to_garbage_collector((void *)ret, INT);
	return (ret);
}

//Function to check if first token is allowed
int	handle_first_node_error(t_minishell *msh)
{
	size_t				i;
	t_cmd				*first_node;
	static const char	*forbidden_tokens[] = {
		"|",
		"<<",
	};

	i = 0;
	first_node = (t_cmd *) msh->cmd->content;
	if (!msh->cmd)
		return (0);
	while (forbidden_tokens[i])
	{
		if (is_identical((char *) forbidden_tokens[i], first_node->cmd))
		{
			msh->parsing_error = syntax_error(first_node->cmd[0]);
			return (1);
		}
		//printf("sdfd%c\n", first_node->cmd[0]);
		i++;
	}
	return (0);
}

void	check_parsing_errors(t_minishell *msh, int end)
{
	t_list	*iter;
	t_cmd	*current;

	iter = msh->cmd;
	current = NULL;
	if (end && handle_first_node_error(msh))
		return ;
	while (iter)
	{
	current = (t_cmd *) iter->content;
		if (is_token(current->cmd[0]) && !current->id) // checks if token is unknown
		{
			msh->parsing_error = syntax_error(current->cmd[0]);
			break ;
		}
		if (!iter->next && end && is_token(current->cmd[0])) // checks if last node id is an operator
			msh->parsing_error = syntax_error('\n');
		//printf("%d\n", current->id);
		//printf("%d\n", end);
		//printf("%d\n", ((t_cmd *)(iter->next->content))->id);
		else if (current->id >= 1 && current->id <= 4 && end && (((t_cmd *)(iter->next->content))->id < 6 || !iter->next))
		    msh->parsing_error = syntax_error(current->cmd[0]);
		iter = iter->next;
	}
}

int	end_quote(int d_quo, int s_quo)
{
	if (d_quo && d_quo % 2 == 0)
		return (1);
	if (s_quo && s_quo % 2 == 0)
		return (1);
	return (0);
}

int	is_quote(t_minishell *msh, int pos, char **cmd)
{
	int		d_quo;
	int		s_quo;
	char	*str;
	char	*ret;	

	str = *cmd;
	ret = NULL;
	d_quo = 0;
	s_quo = 0;
	while (str[pos])
	{
		if (end_quote(d_quo, s_quo))
			break ;
		if (str[pos] == '\"' && s_quo % 2 == 0)
			d_quo++;
		if (str[pos] == '\'' && d_quo % 2 == 0)
			s_quo++;
		get_char(str[pos], &ret);
		pos++;
	}
	if (!end_quote(d_quo, s_quo))
		syntax_error('\n');
	if (ret)
		ft_lstadd_back(&msh->cmd, ft_lstnew((void *)new_cmd(ret, eval_token(ret))));
	return (pos - 1);
}

void	__debug_parsing(t_minishell *msh)
{
	t_list	*iter;
	t_cmd	*current;

	iter = msh->cmd;
	current = NULL;
	while (iter)
	{
		current = (t_cmd *) iter->content;
		printf("{%d}[%s]\n", current->id, current->cmd);
		iter = iter->next;
	}
}