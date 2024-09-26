#include "minishell.h"

t_ast_node *new_ast_node(t_typetoken type)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(t_ast_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->args = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	free_ast(t_ast_node *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	if (node->type == WORD)
	{
		while (node->type == WORD && node->args)
			free(node->args[i++]);
		free(node->args);
	}
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

int	count_args(t_token *current)
{
	int	count;

	count = 0;
	while (current && current->token_type == WORD)
	{
		count++;
		current = current->next;
	}
	return (count);
}