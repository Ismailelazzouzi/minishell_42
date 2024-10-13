#include "minishell.h"

void prepare_ast_nodes_to_execute(t_ast_node *head)
{
	if (head->type != TOKEN_WORD)
	{
        if(!head->file_type)
		    head->file_type = FILE_READY;
        // printf("p1\n");
		if (head->type == TOKEN_REDIR_OUT && head->right)
			head->right->file_type = WRITE_FILE;
		if (head->type == TOKEN_REDIR_APPEND && head->right)
			head->right->file_type = WRITE_FILE_APPEND;
		if (head->type == TOKEN_REDIR_IN && head->right)
        {
            // printf("hear\n");
			head->right->file_type = READ_FILE;
        }
		if (head->type == TOKEN_REDIR_HEREDOC && head->right)
			head->right->file_type = READ_FROM_APPEND;
		if (head->type == TOKEN_PIPE)
		{
			if (head->right)
				head->right->file_type = EXECUTE_FILE;
			if (head->left)
				head->left->file_type = EXECUTE_FILE;
		}
	}
	if (!head->file_type)
		head->file_type = EXECUTE_FILE;
	if (head->left)
		prepare_ast_nodes_to_execute(head->left);
	if (head->right)
		prepare_ast_nodes_to_execute(head->right);
}


void count_red_and_pipes(t_ast_node *head, int *piped)
{
    head->file_type = 0;
    if(head->type == TOKEN_REDIR_OUT || head->type == TOKEN_REDIR_APPEND)
        piped[4] += 1;
    if(head->type == TOKEN_REDIR_IN || head->type == TOKEN_REDIR_HEREDOC)
        piped[3] += 1;
    if(head->type == TOKEN_PIPE)
        piped[5] += 1;
    if(head->left)
        count_red_and_pipes(head->left, piped);
    if(head->right)
        count_red_and_pipes(head->right, piped);
}

