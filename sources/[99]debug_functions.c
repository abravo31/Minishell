#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>


t_list	*ft_lstnew2(void const *content, size_t content_size)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	if (content)
	{
		new_node->content = malloc(content_size);
		if (!new_node->content)
			return (free(new_node), NULL);
		ft_memcpy(new_node->content, content, content_size);
		new_node->content_size = content_size;
	}
	else
	{
		new_node->content = NULL;
		new_node->content_size = 0;
	}
	new_node->next = NULL;
	return (new_node);
}

//cmd ahardcoded cat << EOF > file | wc -c | tr -d " " > file2
t_list	*hardcode_cmds(void)
{
	t_list	*head = NULL;
	t_list	*current = NULL;
	t_cmd	cmd;

	cmd.cmd = "cat";
	cmd.id = UNASSIGNED;
	current = ft_lstnew2(&cmd, sizeof(t_cmd));
	head = current;
	cmd.cmd = "<<";
	cmd.id = L_DREDIR;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "EOF";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = ">";
	cmd.id = R_REDIR;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "file";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "|";
	cmd.id = PIPE;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "wc";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "-c";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "|";
	cmd.id = PIPE;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "tr";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "-d";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = " ";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = ">";
	cmd.id = R_REDIR;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	cmd.cmd = "file2";
	cmd.id = UNASSIGNED;
	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
	current = current->next;
	return (head);
}


//ls  > cat> cat
// t_list	*hardcode_cmds(void)
// {
// 	t_list	*head = NULL;
// 	t_list	*current = NULL;
// 	t_cmd	cmd;

// 	cmd.cmd = ">";
// 	cmd.id = R_REDIR;
// 	current = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	head = current;

// 	cmd.cmd = "file";
// 	cmd.id = UNASSIGNED;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = ">";
// 	cmd.id = R_DREDIR;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = "file2";
// 	cmd.id = UNASSIGNED;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = ">";
// 	cmd.id = R_REDIR;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = "file3";
// 	cmd.id = UNASSIGNED;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;
	
// 	cmd.cmd = ">";
// 	cmd.id = R_DREDIR;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = "file4";
// 	cmd.id = UNASSIGNED;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = ">";
// 	cmd.id = R_REDIR;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = "file5";
// 	cmd.id = UNASSIGNED;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = "cmd1";
// 	cmd.id = UNASSIGNED;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = "arg1";
// 	cmd.id = UNASSIGNED;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = "<";
// 	cmd.id = L_REDIR;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = "file6";
// 	cmd.id = UNASSIGNED;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;
	
// 	cmd.cmd = ">>";
// 	cmd.id = R_DREDIR;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = "file7";
// 	cmd.id = UNASSIGNED;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;
	
// 	cmd.cmd = "<<";
// 	cmd.id = L_DREDIR;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = "file8";
// 	cmd.id = UNASSIGNED;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = "|";
// 	cmd.id = PIPE;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = "tr";
// 	cmd.id = UNASSIGNED;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	return(head);
// }

//harcode cmd but with only one redirection
// t_list	*hardcode_cmds(void)
// {
// 	t_list	*head = NULL;
// 	t_list	*current = NULL;
// 	t_cmd	cmd;

// 	// cmd.cmd = "cat";
// 	// cmd.id = UNASSIGNED;
// 	// current = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	// head = current;

// 	// cmd.cmd = "file1";
// 	// cmd.id = UNASSIGNED;
// 	// current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	// current = current->next;

// 	cmd.cmd = ">";
// 	cmd.id = R_REDIR;
// 	current = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	head = current;

// 	cmd.cmd = "outfile";
// 	cmd.id = UNASSIGNED;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = "cat";
// 	cmd.id = UNASSIGNED;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = ">";
// 	cmd.id = R_REDIR;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	cmd.cmd = "infile";
// 	cmd.id = UNASSIGNED;
// 	current->next = ft_lstnew2(&cmd, sizeof(t_cmd));
// 	current = current->next;

// 	return (head);
// }

//print whole cmd linked list with all the tokens
void	print_cmd(t_list *head)
{
	t_list	*current = head;
	t_cmd	*cmd;
	char	*id[]={"UNASSIGNED", "R_REDIR", "R_DREDIR","L_REDIR","L_DREDIR","PIPE","BUILTIN","D_QUOTE","S_QUOTE","CMD_NAME","CMD_WORD"};

	while (current)
	{
		cmd = (t_cmd *)current->content;
		printf("cmd: %s, id: %s\n", cmd->cmd, id[cmd->id]);
		current = current->next;
	}
}

void	print2DUtil(t_ast *root, int space)
{
	char const	*operators[] = {"PIPE_SEQUENCE", "COMPLEXE_COMMAND", "SIMPLE_COMMAND", "ARGUMENT", "REDIRECTION"};
	char const	*tokens[] = {"UNASSIGNED", "R_REDIR", "R_DREDIR", "L_REDIR", "L_DREDIR", "PIPE", "WORD", "BUILTIN", "D_QUOTE", "S_QUOTE"};

	if (root == NULL)
		return ;
	space += 10;
	print2DUtil(root->right, space);
	ft_printf("\n");
	for (int i = 10; i < space; i++)
		ft_printf(" ");
	if (root->terminal)
	{
		ft_printf("%s\n", tokens[root->id->token]);
		for (int i = 10; i < space; i++)
			ft_printf(" ");
		ft_printf("%s\n",root->data);
	}
	else
		ft_printf("%s\n", operators[root->id->op]);
	print2DUtil(root->left, space);
}