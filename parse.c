#include "minishell.h"

t_ast_node	*parse(t_token **tokens)
{
	t_ast_node	*ast;

	while (*tokens)
	{
		printf("%s\n", (*tokens)->value);
		*tokens = (*tokens)->next;
	}
	ast = NULL;
	return (ast);
}